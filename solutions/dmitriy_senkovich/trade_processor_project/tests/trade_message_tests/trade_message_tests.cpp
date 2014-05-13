#include "test_registrator.h"

#include "trade_message.h"

using namespace trade_processor_project;

void tests_::trade_message_tests()
{
	{
		trade_message tm;

		BOOST_CHECK_NO_THROW( tm.price() );
		BOOST_CHECK_NO_THROW( tm.volume() );
		BOOST_CHECK_NO_THROW( tm.security_symbol() );
		BOOST_CHECK_NO_THROW( tm.minute() );
		BOOST_CHECK_NO_THROW( tm.price_denominator_indicator() );
		BOOST_CHECK_EQUAL( tm.security_symbol(), "\0" );
		BOOST_CHECK_EQUAL( tm.price(), 0 );
		BOOST_CHECK_EQUAL( tm.volume(), 0 );
		BOOST_CHECK_EQUAL( tm.minute(), 0 );
		BOOST_CHECK_EQUAL( tm.price_denominator_indicator(), "\0" );
	}
	{
		trade_message tm;
		std::stringstream test_stream;

		char minute = 48;
		tm.set_minute() = static_cast<boost::uint32_t> ( minute ) - 48; 

		BOOST_CHECK_EQUAL( tm.minute(), 0 );
	}
}
