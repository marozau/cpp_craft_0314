#include "test_registrator.h"

#include <tcp_client.h>

#include <boost/thread.hpp>

namespace async_tcp
{
	namespace tests_
	{
		namespace detail
		{
			class tcp_client_manager_test : public tcp_client_manager
			{
			public:
				virtual void message_read();
				virtual void message_sent();
				virtual ~tcp_client_manager_test();
			};
			class async_tcp_helper 
			{
				boost::asio::io_service io_service_;
				boost::asio::ip::tcp::acceptor acceptor_;

				boost::asio::ip::tcp::socket socket_;
				boost::thread thread_;

			public:
				explicit async_tcp_helper( const unsigned short port );
				void send();
				void check_connection();
				void close_socket();
			private:
				void open_socket_wait_for_connect_();
			};
		}
	}
}

void async_tcp::tests_::detail::tcp_client_manager_test::message_read()
{
}
void async_tcp::tests_::detail::tcp_client_manager_test::message_sent()
{
}
async_tcp::tests_::detail::tcp_client_manager_test::~tcp_client_manager_test()
{
}

//
async_tcp::tests_::detail::async_tcp_helper::async_tcp_helper( const unsigned short port )
	: io_service_()
	, acceptor_( io_service_, boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4() , port ) )
	, socket_( io_service_ )
{
	thread_ = boost::thread( boost::bind( &async_tcp_helper::open_socket_wait_for_connect_, this ) );
}
void async_tcp::tests_::detail::async_tcp_helper::send()
{
	BOOST_CHECK_EQUAL( socket_.is_open(), true );
	size_t l = 5;
	socket_.send( boost::asio::buffer( &l, sizeof(size_t) ) );
	socket_.send( boost::asio::buffer( "hello", 5 ) );
}
void async_tcp::tests_::detail::async_tcp_helper::check_connection()
{
	thread_.join();
	BOOST_CHECK_EQUAL( socket_.is_open(), true );
}
void async_tcp::tests_::detail::async_tcp_helper::close_socket()
{
	BOOST_CHECK_NO_THROW( socket_.close() );
	BOOST_CHECK_NO_THROW( acceptor_.close() );
}
void async_tcp::tests_::detail::async_tcp_helper::open_socket_wait_for_connect_()
{
	acceptor_.accept( socket_ );
}

//
void async_tcp::tests_::async_tests_work()
{			
	// this test dependent on tcp port availability, please be sure that 50000 port is free
	static const unsigned short port = 50000;		
	detail::tcp_client_manager_test tcp_manager; 
	{
		detail::async_tcp_helper helper( port );
		boost::this_thread::sleep( boost::posix_time::milliseconds( 10 ) );
		tcp_client client( tcp_manager, "127.0.0.1", port );
		boost::this_thread::sleep( boost::posix_time::milliseconds( 10 ) );
		BOOST_CHECK_NO_THROW( helper.check_connection() );
		BOOST_CHECK_NO_THROW( helper.close_socket() );
	}
	{
		detail::async_tcp_helper helper( port );
		boost::this_thread::sleep( boost::posix_time::milliseconds( 10 ) );
		tcp_client client( tcp_manager, "127.0.0.1", port );
		boost::this_thread::sleep( boost::posix_time::milliseconds( 10 ) );
		BOOST_CHECK_NO_THROW( helper.send() );
		BOOST_CHECK_NO_THROW( helper.check_connection() );
		boost::this_thread::sleep( boost::posix_time::milliseconds( 10 ) );
		BOOST_CHECK_NO_THROW( helper.close_socket() );
	}
	{
		detail::async_tcp_helper helper( port );
		boost::this_thread::sleep( boost::posix_time::milliseconds( 10 ) );
		tcp_client client( tcp_manager, "127.0.0.1", port );
		boost::this_thread::sleep( boost::posix_time::milliseconds( 10 ) );
		BOOST_CHECK_NO_THROW( client.write( "test", 4 ) );
		BOOST_CHECK_NO_THROW( helper.check_connection() );
		boost::this_thread::sleep( boost::posix_time::milliseconds( 10 ) );
		BOOST_CHECK_NO_THROW( helper.close_socket() );
	}
}
