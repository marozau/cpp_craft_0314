#include "test_registrator.h"

#include <quote_message.h>
#include <fstream>


namespace multicast_communication
{
	namespace tests_
	{
		void quote_callback( const quote_message_ptr& msg )
		{
			BOOST_CHECK_EQUAL( msg->security_symbol(), "ADM" );
			BOOST_CHECK_EQUAL( msg->bid_price(), 4147 );
			BOOST_CHECK_EQUAL( msg->bid_volume(), 6 );
			BOOST_CHECK_EQUAL( msg->offer_price(), 4148 );
			BOOST_CHECK_EQUAL( msg->offer_volume(), 4 );
			BOOST_CHECK_EQUAL( msg->minute(), 626 );
		}
	}
}

void multicast_communication::tests_::quote_message_tests()
{
	quote_message_ptr msg_ptr( new quote_message( &quote_callback ) );

	std::ifstream test_input( SOURCE_DIR "/tests/data/quote_tests.txt" );
	std::string msg;
	std::getline( test_input, msg );
	test_input.close();
	std::stringstream stream( msg.substr( 1 ) );

	BOOST_CHECK_NO_THROW( msg_ptr->parse( stream ) );

	std::stringstream error_stream( "Error message" );

	BOOST_CHECK_THROW( msg_ptr->parse( error_stream ), std::exception );
}
