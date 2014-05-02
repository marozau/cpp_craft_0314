#include "test_registrator.h"

#include <trade_message.h>

void multicast_communication::tests_::trade_message_tests()
{
	BOOST_CHECK_NO_THROW
	(
		const trade_message tm;

		BOOST_CHECK_EQUAL( tm.security_symbol(), "" );
		BOOST_CHECK_EQUAL( tm.price(), 0.0 );
		BOOST_CHECK_EQUAL( tm.volume(), 0.0 );
	)
	
	BOOST_CHECK_NO_THROW
	(
		const std::string ss("AO A  000140208P:3\\806BGS@0100D00330400DF ");
						
	
		const trade_message_ptr tm =trade_message_ptr(new trade_message (ss,SHORT_T));
		
		tm->segmentation(ss, SHORT_T);
		
		BOOST_CHECK_EQUAL( tm->security_symbol(), "BGS" );
		BOOST_CHECK_EQUAL( tm->price(),  330400);
		BOOST_CHECK_EQUAL( tm->volume(), 100.0);
		
	)
	
		BOOST_CHECK_NO_THROW
	(
		const std::string ss("AO A  000146235T:3]008ACN@0100B00007790DD ");
	
		const trade_message_ptr tm =trade_message_ptr(new trade_message (ss,SHORT_T));
		
		tm->segmentation(ss, SHORT_T);
		
		BOOST_CHECK_EQUAL( tm->security_symbol(), "ACN" );
		BOOST_CHECK_EQUAL( tm->price(),  7790);
		BOOST_CHECK_EQUAL( tm->volume(), 100.0);
		
	)
	BOOST_CHECK_NO_THROW
	(
		const std::string ss("AO A  000146234N:3]004ACN             0     000 F  1  D000000779000000000100DD 0");
						
		const trade_message_ptr tm =trade_message_ptr(new trade_message (ss,LONG_T));
		
		tm->segmentation(ss, LONG_T);
	
		BOOST_CHECK_EQUAL( tm->security_symbol(), "ACN        " );
		BOOST_CHECK_EQUAL( tm->price(), 779000 );
		BOOST_CHECK_EQUAL( tm->volume(), 100.0 );
	)
}
