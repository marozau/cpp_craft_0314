#include "test_registrator.h"

#include <trade_message.h>

void multicast_communication::tests_::trade_message_tests()
{
	BOOST_CHECK_NO_THROW
	(
		trade_message tm;

		BOOST_CHECK_EQUAL( tm.security_symbol(), "" );
		BOOST_CHECK_EQUAL( tm.price(), 0.0 );
		BOOST_CHECK_EQUAL( tm.volume(), 0.0 );
	)

	BOOST_CHECK_NO_THROW
	(
		const std::string input_string = "AOAO A  000146237T:3]010ACN@0100B00007790DD ";
		const trade_message_ptr tm(new multicast_communication::trade_message(input_string));

		BOOST_CHECK_EQUAL( tm->security_symbol(), "" );
		BOOST_CHECK_EQUAL( tm->price(), 0.0 );
		BOOST_CHECK_EQUAL( tm->volume(), 0.0 );
		BOOST_CHECK_EQUAL( tm->hours(),  0 );
		BOOST_CHECK_EQUAL( tm->minutes(),  0 );
	)

	BOOST_CHECK_NO_THROW
	(
		const std::string input_string = "EIAO A  000146237T:3]010ACN@0100B00007790DD ";
		const trade_message_ptr tm(new multicast_communication::trade_message(input_string));

		BOOST_CHECK_EQUAL( tm->security_symbol(), "ACN" );
		BOOST_CHECK_EQUAL( tm->price(), 77.9 );
		BOOST_CHECK_EQUAL( tm->volume(), 100.0 );
		BOOST_CHECK_EQUAL( tm->hours(),  10 );
		BOOST_CHECK_EQUAL( tm->minutes(),  3 );
	)

	BOOST_CHECK_NO_THROW
	(
		const std::string input_string = "EBAO A  000146234N:3]004ACN             0     000 F  1  D000000779000000000100DD 0";
		const trade_message_ptr tm(new multicast_communication::trade_message(input_string));

		BOOST_CHECK_EQUAL( tm->security_symbol(), "ACN" );
		BOOST_CHECK_EQUAL( tm->price(), 77.9 );
		BOOST_CHECK_EQUAL( tm->volume(), 100.0 );
		BOOST_CHECK_EQUAL( tm->hours(),  10 );
		BOOST_CHECK_EQUAL( tm->minutes(),  3 );
	)
}
