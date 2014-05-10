#include "test_registrator.h"

#include <trade_message.h>
#include <fstream>

namespace multicast_communication
{
	namespace tests_
	{
		void trade_callback( const trade_message_ptr& msg )
		{
			BOOST_CHECK_EQUAL( msg->security_symbol(), "ACN" );
			BOOST_CHECK_EQUAL( msg->price(), 779000 );
			BOOST_CHECK_EQUAL( msg->volume(), 100 );
			BOOST_CHECK_EQUAL( msg->minute(), 603 );
		}
	}
}

void multicast_communication::tests_::trade_message_tests()
{
	trade_message_ptr msg_ptr( new trade_message( &trade_callback ) );

	std::ifstream test_input( SOURCE_DIR "/tests/data/trade_tests.txt" );
	std::string msg;
	std::getline( test_input, msg );
	test_input.close();
	std::stringstream stream( msg.substr( 1 ) );

	BOOST_CHECK_NO_THROW( msg_ptr->parse( stream ) );	

	std::stringstream error_stream( "Error message" );
	BOOST_CHECK_THROW( msg_ptr->parse( error_stream ), std::exception );
}
