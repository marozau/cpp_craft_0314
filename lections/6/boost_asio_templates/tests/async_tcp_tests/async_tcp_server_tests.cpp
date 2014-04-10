#include "test_registrator.h"

#include <tcp_server.h>

#include <boost/thread.hpp>

void async_tcp::tests_::async_tcp_server_constructor_tests()
{
	typedef boost::shared_ptr< tcp_server > server_ptr;
	const unsigned short port = 50000;
	{
		server_ptr s;				
		BOOST_CHECK_NO_THROW( s.reset( new tcp_server( port ) ) );
	}			
}
void async_tcp::tests_::async_tcp_server_tests()
{
	typedef boost::shared_ptr< tcp_server > server_ptr;
	const unsigned short port = 50000;
	{
		using namespace boost::asio;
		server_ptr s;				
		BOOST_CHECK_NO_THROW( s.reset( new tcp_server( port ) ) );
		ip::tcp::endpoint ep( ip::address::from_string( "127.0.0.1" ), port );

		io_service service;
		ip::tcp::socket socket( service );
		socket.connect( ep );
		boost::this_thread::sleep( boost::posix_time::milliseconds( 10 ) );

		const std::string login = "login";
		const size_t login_size = login.size();
		write( socket, buffer( &login_size, sizeof( login_size ) ) );
		boost::this_thread::sleep( boost::posix_time::milliseconds( 10 ) );
		write( socket, buffer( login.c_str(), login_size ) );
		boost::this_thread::sleep( boost::posix_time::milliseconds( 10 ) );

		char* buff_length[ sizeof( size_t ) ];
		read( socket, buffer( buff_length, sizeof( size_t ) ) );				
		const size_t answer_size = *reinterpret_cast< const size_t* >( buff_length );
		BOOST_CHECK_EQUAL( answer_size, 2ul );
		char* buff_answer = new char[ answer_size ];
		read( socket, buffer( buff_answer, answer_size ) );
		const std::string expected_answer( "ok" );
		BOOST_CHECK_EQUAL( memcmp( expected_answer.c_str(), buff_answer, expected_answer.size() ), 0 );
		delete [] buff_answer;
	}
}
