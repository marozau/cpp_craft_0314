#include "tcp_server.h"

#include <boost/bind.hpp>

using namespace async_tcp;

tcp_server::tcp_server( const unsigned short port )
	: service_()
	, acc_( service_, boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4(), port ) )
{
	wait_for_connection_();
	service_thread_ = boost::thread( boost::bind( &tcp_server::run_service_, this ) );
}
tcp_server::~tcp_server()
{
	acc_.close();
	service_.stop();
	service_thread_.join();
}
void tcp_server::wait_for_connection_()
{
	using namespace boost::asio::ip;
	clients_.push_back( client_ptr( new client_manager( service_ ) ) );
	acc_.async_accept( *clients_.back()->socket_, boost::bind( &tcp_server::handle_accept_, this, _1 ) );
}
void tcp_server::handle_accept_( const boost::system::error_code& er )
{
	using namespace boost::asio;
	if ( er )
		return;	
	client_ptr& cm = clients_.back();
	cm->socket_->async_receive( buffer( &cm->message_length_, sizeof( cm->message_length_ ) ), boost::bind( &tcp_server::on_read_length_, this, boost::ref( cm ), _1 ) );
	wait_for_connection_();
}
void tcp_server::on_read_length_( client_ptr& cm, const boost::system::error_code& er )
{
	using namespace boost::asio;
	if ( er )
		return;	
	cm->socket_->async_receive( buffer( cm->get_buffer(), cm->message_length_ ), boost::bind( &tcp_server::on_read_, this, boost::ref( cm ), _1 ) );
}
void tcp_server::on_read_( client_ptr& cm, const boost::system::error_code& er )
{
	using namespace boost::asio;
	if ( er )
		return;
	const size_t size = 2;
	cm->socket_->async_send( buffer( &size, sizeof( size ) ), boost::bind( &tcp_server::on_write_length_, this, boost::ref( cm ), _1 ) );
}
void tcp_server::on_write_length_( client_ptr& cm, const boost::system::error_code& er )
{
	using namespace boost::asio;
	if ( er )
		return;
	cm->socket_->async_send( buffer( "ok", 2 ), boost::bind( &tcp_server::on_write_length_, this, boost::ref( cm ), _1 ) );
}
void tcp_server::on_write_( client_ptr& cm, const boost::system::error_code& er )
{
	using namespace boost::asio;
	if ( er )
		return;
	clients_.remove( cm );
}
void tcp_server::run_service_()
{
	service_.run();
}