#include "udp_listener.h"

#include <boost/bind.hpp>

namespace multicast_communication
{
	const size_t async_udp::udp_listener::buffer_size = 2000ul;

	async_udp::udp_listener::udp_listener( boost::asio::io_service& io_service, const std::string& multicast_address, unsigned short port, communication& callback_communication, message_type client_type )
		: io_service_( io_service )
		, listen_endpoint_( boost::asio::ip::address::from_string( "0.0.0.0" ), port )
		, socket_( io_service_ )
		, multicast_address_( multicast_address )
		, buffer( new std::string( buffer_size, '\0' ) )
		, callback_communication( callback_communication )
		, client_type( client_type )
	{
		socket_reload_();
		register_listen_();
	}
	async_udp::udp_listener::~udp_listener()
	{
	}
	void async_udp::udp_listener::socket_reload_()
	{
		using boost::asio::ip::udp;
		using boost::asio::ip::address;
		using boost::asio::ip::multicast::join_group;

		socket_.open( listen_endpoint_.protocol() );
		socket_.set_option( udp::socket::reuse_address( true ) );
		socket_.bind( listen_endpoint_ );
		socket_.set_option( join_group( address::from_string( multicast_address_ ) ) );
	}
	void async_udp::udp_listener::register_listen_()
	{
		char* const buffer_start = &(*buffer->begin());

		using namespace boost::asio::placeholders;
		socket_.async_receive( boost::asio::buffer( buffer_start, buffer_size ), 
			boost::bind( &udp_listener::listen_handler_, this, buffer, error ) ); // ,bytes_transferred ) );
	}

	void async_udp::udp_listener::listen_handler_( buffer_type buffer, const boost::system::error_code& error )//, const size_t bytes_received )
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
			callback_communication.push_message( *buffer, client_type );
			register_listen_();
		}
	}
}