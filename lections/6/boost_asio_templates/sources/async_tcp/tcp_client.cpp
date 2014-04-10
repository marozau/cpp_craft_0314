#include "tcp_client.h"

#include <boost/bind.hpp>

using namespace async_tcp;

tcp_client_manager::tcp_client_manager()
	: buffer_( NULL )
{
}
tcp_client_manager::~tcp_client_manager() 
{
	delete [] buffer_;
	buffer_ = NULL;
}
char* tcp_client_manager::get_buffer( const size_t size )
{
	delete [] buffer_;
	buffer_ = new char[ size ];
	return buffer_;
}

tcp_client::tcp_client( tcp_client_manager& manager, const std::string& ip_address, const unsigned short port )
	: manager_( manager )
	, io_service_()
	, socket_( io_service_ )
{
	using namespace boost::asio::ip;
	socket_.connect( tcp::endpoint( address::from_string( ip_address ), port ) );

	socket_.async_receive( boost::asio::buffer( &length_, sizeof( length_ ) ), boost::bind( &tcp_client::read_string_length_handler_, this, _1 ) );

	service_ = boost::thread( boost::bind( &tcp_client::run_service_, this ) );
}
tcp_client::~tcp_client()
{
	io_service_.stop();
	service_.join();
}
void tcp_client::write( const char* const data, const size_t size )
{
	socket_.async_send( boost::asio::buffer( data, size ), boost::bind( &tcp_client::write_string_handler_, this, _1 ) );
}
void tcp_client::read_string_length_handler_( const boost::system::error_code& er )
{
	if ( er )
		return;
	char* buffer = manager_.get_buffer( length_ );
	socket_.async_receive( boost::asio::buffer( buffer, length_ ), boost::bind( &tcp_client::read_string_handler_, this, _1 ) );
}
void tcp_client::read_string_handler_( const boost::system::error_code& er )
{
	if (er)
		return;
	manager_.message_read();	
	socket_.async_receive( boost::asio::buffer( &length_, sizeof( length_ ) ), boost::bind( &tcp_client::read_string_length_handler_, this, _1 ) );
}
void tcp_client::write_string_handler_( const boost::system::error_code& )
{
	manager_.message_sent();
}

void tcp_client::run_service_()
{
	io_service_.run();
}

