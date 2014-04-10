#include "test_registrator.h"

#include <tcp_client.h>

#include <boost/thread.hpp>
#include <boost/cstdint.hpp>

namespace sync_tcp
{
	namespace tests_
	{
		namespace detail
		{
			class tcp_client_test_helper : protected virtual boost::noncopyable
			{
				boost::asio::io_service io_service_;
				boost::asio::ip::tcp::acceptor acceptor_;
				//
				boost::asio::ip::tcp::socket socket_;
				boost::thread thread_;
			public:
				explicit tcp_client_test_helper( const unsigned short port );
				void check_connection();
				void close_socket();
			private:
				void open_socket_wait_for_connect_();
			};
		}
	}
}

sync_tcp::tests_::detail::tcp_client_test_helper::tcp_client_test_helper( const unsigned short port )
	: io_service_()
	, acceptor_( io_service_, boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4() , port ) )
	, socket_( io_service_ )
{
	thread_ = boost::thread( boost::bind( &tcp_client_test_helper::open_socket_wait_for_connect_, this ) );
}
void sync_tcp::tests_::detail::tcp_client_test_helper::check_connection()
{
	thread_.join();
	BOOST_CHECK_EQUAL( socket_.is_open(), true );
}
void sync_tcp::tests_::detail::tcp_client_test_helper::close_socket()
{
	BOOST_CHECK_NO_THROW( socket_.close() );
	BOOST_CHECK_NO_THROW( acceptor_.close() );
}
void sync_tcp::tests_::detail::tcp_client_test_helper::open_socket_wait_for_connect_()
{
	acceptor_.accept( socket_ );
}


//
void sync_tcp::tests_::tcp_client_constructor_tests() 
{
	// this test dependent on tcp port availability, please be sure that 50000 port is free

	static const unsigned short port = 50000;
	BOOST_CHECK_THROW( ( tcp_client ( "127.0.0.1", port ) ), boost::system::system_error );

	{
		detail::tcp_client_test_helper helper( port );
		BOOST_CHECK_NO_THROW( ( tcp_client ( "127.0.0.1", port ) ) );
		helper.check_connection();
		helper.close_socket();
	}
	{
		detail::tcp_client_test_helper helper( port );
		tcp_client client( "127.0.0.1", port );
		helper.check_connection();
		helper.close_socket();
		boost::uint32_t data( 0 );
		BOOST_CHECK_NO_THROW( client.write( &data, sizeof( boost::uint32_t ) ) );
	}
	{
		detail::tcp_client_test_helper helper( port );
		tcp_client client( "127.0.0.1", port );
		helper.check_connection();
		helper.close_socket();
		boost::uint32_t data( 0 );
		BOOST_CHECK_THROW( client.read( &data, sizeof( boost::uint32_t ) ), boost::system::system_error );
	}
	{
		detail::tcp_client_test_helper helper( port );
		tcp_client client( "127.0.0.1", port );
		helper.check_connection();
		helper.close_socket();
		BOOST_CHECK_NO_THROW( client.read( NULL, 0ul ) );
	}
}
