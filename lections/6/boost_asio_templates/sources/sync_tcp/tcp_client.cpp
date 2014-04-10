#include "tcp_client.h"

#include <boost/asio/buffer.hpp>

sync_tcp::tcp_client::tcp_client( const std::string& ip_address, const unsigned short port )
: io_service_()
, socket_( io_service_ )
{
	using namespace boost::asio;
	socket_.connect( ip::tcp::endpoint( ip::address::from_string( ip_address ), port ) );
}
void sync_tcp::tcp_client::read( char* const data, const size_t size )
{
	boost::asio::read( socket_, boost::asio::buffer( data, size ), boost::asio::transfer_all() );
}
void sync_tcp::tcp_client::write( const char* const data, const size_t size )
{
	boost::asio::write( socket_, boost::asio::buffer( data, size ), boost::asio::transfer_all() );
}
