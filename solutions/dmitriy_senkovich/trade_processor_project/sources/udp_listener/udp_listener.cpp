#include "udp_listener.h"
#include <boost/bind.hpp>

using namespace trade_processor_project;

bool udp_listener::to_stop = false;
boost::mutex udp_listener::lock_to_stop;
boost::mutex udp_listener::lock_trade_queue_;
boost::mutex udp_listener::lock_quote_queue_;
boost::condition_variable udp_listener::trade_cond_var_;
boost::condition_variable udp_listener::quote_cond_var_;

udp_listener::udp_listener( boost::asio::io_service& io_service, const std::string& multicast_address, unsigned short port, bool trade, std::queue< buffer_type >& block_message_queue )
	:io_service_( io_service )
	,listen_endpoint_( boost::asio::ip::address::from_string( "0.0.0.0" ), port )
	,socket_( io_service_ )
	,multicast_address_( multicast_address )
	,trade_( trade )
	,buffer_( new std::string( default_buffer_size, '\0' ) )
	,block_message_queue_( block_message_queue )
{  
	socket_reload_();
	register_listen_();
}
std::queue< udp_listener::buffer_type >& udp_listener::messages()
{
	if( trade_ )
		boost::mutex::scoped_lock lock( lock_trade_queue_ );
	else
		boost::mutex::scoped_lock lock( lock_quote_queue_ );

	return block_message_queue_;
}
void udp_listener::socket_reload_()
{
	using boost::asio::ip::udp;
	using boost::asio::ip::address;
	using boost::asio::ip::multicast::join_group;

	socket_.open( listen_endpoint_.protocol() );
	socket_.set_option( udp::socket::reuse_address( true ) );
	socket_.bind( listen_endpoint_ );
	socket_.set_option( join_group( address::from_string( multicast_address_ ) ) );
}
void udp_listener::register_listen_()
{
	char* const buffer_start = &(*buffer_->begin());

	using namespace boost::asio::placeholders;
	socket_.async_receive( boost::asio::buffer( buffer_start, default_buffer_size ), 
		boost::bind( &udp_listener::listen_handler_, this, buffer_, error, bytes_transferred ) );
}

void udp_listener::listen_handler_( buffer_type bt, const boost::system::error_code& error, const size_t bytes_received )
{
	if ( error )
	{
		static const int NO_ENOUGHT_BUFFER = 234;
		if ( error.value() == NO_ENOUGHT_BUFFER )
		{
			register_listen_();
		}
		return;
	}
	else
	{
		if( trade_ )
		{
			boost::unique_lock< boost::mutex > lock( lock_trade_queue_ );
			{
				boost::mutex::scoped_lock lock( udp_listener::lock_to_stop );
				if( udp_listener::to_stop )
					return;
			}
			block_message_queue_.push( buffer_type( new std::string( bt->c_str(), bytes_received ) ) );
			trade_cond_var_.notify_one();
			lock.unlock();
		}
		else
		{
			boost::unique_lock< boost::mutex > lock( lock_quote_queue_ );
			{
				boost::mutex::scoped_lock lock( udp_listener::lock_to_stop );
				if( udp_listener::to_stop )
					return;
			}
			block_message_queue_.push( buffer_type( new std::string( bt->c_str(), bytes_received ) ) );
			quote_cond_var_.notify_one();
			lock.unlock();
		}
		register_listen_();
	}
}