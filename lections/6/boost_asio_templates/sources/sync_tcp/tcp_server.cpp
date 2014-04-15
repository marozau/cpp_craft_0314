#include "tcp_server.h"

sync_tcp::tcp_server::tcp_server( const unsigned short port )
 : io_service_()
 , acceptor_( io_service_, boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4() , port ) )
{
}
sync_tcp::tcp_server::~tcp_server()
{
	acceptor_.close();
}
sync_tcp::tcp_server::client_socket sync_tcp::tcp_server::wait_for_connection()
{
	client_socket new_connection( new boost::asio::ip::tcp::socket( io_service_ ) );
	acceptor_.accept( *new_connection );
	client_sockets_.push_back( new_connection );
	return client_sockets_.back();
}
//
void sync_tcp::tcp_server::read( client_socket& socket, char* const data, const size_t size )
{
	boost::asio::read( *socket, boost::asio::buffer( data, size ), boost::asio::transfer_all() );
}
void sync_tcp::tcp_server::write( client_socket& socket, const char* const data, const size_t size )
{
	boost::asio::write( *socket, boost::asio::buffer( data, size ), boost::asio::transfer_all() );
}
