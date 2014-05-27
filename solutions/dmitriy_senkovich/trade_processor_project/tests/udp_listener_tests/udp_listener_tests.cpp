#include "test_registrator.h"

#include "udp_listener.h"

#include <cstring>
#include <boost/asio.hpp>

using namespace trade_processor_project;

typedef boost::shared_ptr< std::string > buffer_type;

void service_thread( boost::asio::io_service& service )
{	
	service.run();
}

void tests_::udp_listener_tests()
{
	{
		BOOST_CHECK_NO_THROW
		( 
			boost::asio::io_service service;
			std::queue< buffer_type > block_message_queue;
			bool trade = true;
			udp_listener uw( service, "224.0.0.0", 50000, trade, block_message_queue );
		);
	}
	{
		boost::asio::io_service service;
		std::queue< buffer_type > block_message_queue;
		bool trade = true;
		udp_listener uw( service, "224.0.0.0", 50000, trade, block_message_queue );

		const std::string buffer( "hello world" );
		boost::asio::ip::udp::endpoint endpoint( boost::asio::ip::address::from_string( "224.0.0.0" ), 50000 ); 
		boost::asio::ip::udp::socket socket( service, endpoint.protocol() );
		boost::thread receive_messages( boost::bind( service_thread, boost::ref( service ) ) );
		while( uw.messages().empty() )
		{
			socket.send_to( boost::asio::buffer( buffer ), endpoint );
			boost::this_thread::sleep_for( boost::chrono::nanoseconds( 1 ) );
		}
		service.stop();
		receive_messages.join();
		BOOST_CHECK_EQUAL( strcmp( uw.messages().front()->c_str(), "hello world" ), 0 );
	}
	{
		boost::asio::io_service service;
		std::queue< buffer_type > block_message_queue;
		bool trade = true;
		udp_listener uw( service, "224.0.0.0", 50000, trade, block_message_queue );

		const std::string buffer( "smells like teen spirit!!!" );
		boost::asio::ip::udp::endpoint endpoint( boost::asio::ip::address::from_string( "224.0.0.0" ), 50000 ); 
		boost::asio::ip::udp::socket socket( service, endpoint.protocol() );
		boost::thread receive_messages( boost::bind( service_thread, boost::ref( service ) ) );
		while( uw.messages().empty() )
		{
			socket.send_to( boost::asio::buffer( buffer.c_str(), buffer.size() ), endpoint );
			boost::this_thread::sleep_for( boost::chrono::nanoseconds( 1 ) );
		}
		service.stop();
		receive_messages.join();
		BOOST_CHECK_EQUAL( strcmp( uw.messages().front()->c_str(), "smells like teen spirit!!!"), 0 );
	}
	{
		boost::asio::io_service service;
		std::queue< buffer_type > block_message_queue;
		bool trade = true;
		udp_listener uw( service, "224.0.0.0", 50000, trade, block_message_queue );

		boost::asio::ip::udp::endpoint endpoint( boost::asio::ip::address::from_string( "224.0.0.0" ), 50000 ); 
		boost::asio::ip::udp::socket socket( service, endpoint.protocol() );
		boost::thread receive_messages( boost::bind( service_thread, boost::ref( service ) ) );

		const std::string first( "firstmessage" );
		socket.send_to( boost::asio::buffer( first.c_str(), first.size() ), endpoint );

		const std::string second( "second msg" );
		socket.send_to( boost::asio::buffer( second.c_str(), second.size() ), endpoint );

		const std::string third( "th3msg" );
		socket.send_to( boost::asio::buffer( third.c_str(), third.size() ), endpoint );

		const std::string fourth( "4th mess" );
		socket.send_to( boost::asio::buffer( fourth.c_str(), fourth.size() ), endpoint );

		while( uw.messages().size() < 4ul )
		{
			socket.send_to( boost::asio::buffer( fourth.c_str(), fourth.size() ), endpoint );
			boost::this_thread::sleep_for( boost::chrono::nanoseconds( 1 ) );
		}
		service.stop();
		receive_messages.join();

		BOOST_CHECK_EQUAL( block_message_queue.empty(), false );
		BOOST_CHECK_EQUAL( strcmp( block_message_queue.front()->c_str(), "firstmessage" ), 0 );

		std::vector< std::string > messages;
		while( !uw.messages().empty() )
		{
			messages.push_back( *( uw.messages().front() ) );
			uw.messages().pop();
		}
		const std::string string_unite( "firstmessage, second msg, th3msg, 4th mess" );
		for ( std::vector< std::string >::const_iterator i = messages.begin() ; i != messages.end() ; ++i )
			BOOST_CHECK_EQUAL( ( string_unite.find( i->c_str() ) != std::string::npos ), true );

		BOOST_CHECK_EQUAL( block_message_queue.empty(), true );
	}

}
