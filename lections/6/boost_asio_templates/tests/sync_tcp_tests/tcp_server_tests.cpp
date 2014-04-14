#include "test_registrator.h"

#include <tcp_server.h>

#include <boost/thread.hpp>
#include <boost/cstdint.hpp>

namespace sync_tcp
{
	namespace tests_
	{
		namespace detail
		{
			void tcp_server_accept( tcp_server& server );
			class tcp_server_test_helper : protected virtual boost::noncopyable
			{
				boost::asio::io_service io_service_;
				boost::asio::ip::tcp::socket socket_;
			public:
				explicit tcp_server_test_helper();
				~tcp_server_test_helper();
				//
				void connect( const unsigned short port );
			};
		}
	}
}

void sync_tcp::tests_::detail::tcp_server_accept( tcp_server& server )
{
	server.wait_for_connection();
}

sync_tcp::tests_::detail::tcp_server_test_helper::tcp_server_test_helper()
: io_service_()
, socket_( io_service_ )
{
}
void sync_tcp::tests_::detail::tcp_server_test_helper::connect( const unsigned short port )
{
	using namespace boost::asio;
	socket_.connect( ip::tcp::endpoint( ip::address::from_string( "127.0.0.1" ), port ) );
}
sync_tcp::tests_::detail::tcp_server_test_helper::~tcp_server_test_helper()
{
}

void sync_tcp::tests_::tcp_server_constructor_tests()
{
	// this test dependent on tcp port availability, please be sure that 50000 port is free

	static const unsigned short port = 50000;

	{
		BOOST_CHECK_NO_THROW( ( tcp_server( port ) ) );
		detail::tcp_server_test_helper helper;
		BOOST_CHECK_THROW( helper.connect( port ), boost::system::system_error );
	}
	{
		tcp_server server( port );
		detail::tcp_server_test_helper helper;
		boost::thread accept_thread( boost::bind( &detail::tcp_server_accept, boost::ref( server ) ) );
		boost::this_thread::sleep_for( boost::chrono::milliseconds( 0 ) );
		BOOST_CHECK_NO_THROW( helper.connect( port ) );
		accept_thread.join();
	}
}
