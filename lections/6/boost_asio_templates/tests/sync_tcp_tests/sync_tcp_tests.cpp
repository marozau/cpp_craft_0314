#include "test_registrator.h"

#include <tcp_client.h>
#include <tcp_server.h>

#include <boost/thread.hpp>
#include <boost/cstdint.hpp>

#include <boost/array.hpp>

namespace sync_tcp
{
	namespace tests_
	{
		namespace detail
		{
			class sync_tcp_helper
			{
				static const size_t buffer_size = 6;
				static const std::string password;
				static const std::string answer;
			public:
				static void server_thread( tcp_server& server );
				static void client_thread( tcp_client& client );
			};
		}
	}
}

const std::string sync_tcp::tests_::detail::sync_tcp_helper::password = "hello";
const std::string sync_tcp::tests_::detail::sync_tcp_helper::answer = "world";

void sync_tcp::tests_::detail::sync_tcp_helper::server_thread( tcp_server& server )
{
	tcp_server::client_socket connection = server.wait_for_connection();
	server.write( connection, password.c_str(), password.size() );
	boost::array< char, buffer_size > buffer;
	server.read( connection, buffer.data(), answer.size() );
	BOOST_CHECK_EQUAL( memcmp( answer.c_str(), buffer.data(), answer.size() ), 0 );
}
void sync_tcp::tests_::detail::sync_tcp_helper::client_thread( tcp_client& client )
{
	boost::array< char, buffer_size > buffer;
	client.read( buffer.data(), password.size() );
	BOOST_CHECK_EQUAL( memcmp( password.c_str(), buffer.data(), password.size() ), 0  );
	client.write( answer.c_str(), answer.size() );
}

void sync_tcp::tests_::tcp_sync_full_cyrcle_tests()
{
	// this test dependent on tcp port availability, please be sure that 50000 port is free
	static const unsigned short port = 50000;

	tcp_server server( port );
	boost::thread server_thread( boost::bind( &detail::sync_tcp_helper::server_thread, boost::ref( server ) ) );
	boost::this_thread::sleep_for( boost::chrono::milliseconds( 10 ) );
	tcp_client client( "127.0.0.1", port );
	detail::sync_tcp_helper::client_thread( client );
	server_thread.join();
}
