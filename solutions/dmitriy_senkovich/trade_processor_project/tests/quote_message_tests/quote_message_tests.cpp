#include "test_registrator.h"

#include "quote_message.h"

using namespace trade_processor_project;

void tests_::quote_message_tests()
{
	{
		quote_message qm;

		BOOST_CHECK_NO_THROW( qm.bid_price() );
		BOOST_CHECK_NO_THROW( qm.bid_volume() );
		BOOST_CHECK_NO_THROW( qm.offer_price() );
		BOOST_CHECK_NO_THROW( qm.offer_volume() );
		BOOST_CHECK_NO_THROW( qm.security_symbol() );
		BOOST_CHECK_NO_THROW( qm.minute() );
		BOOST_CHECK_NO_THROW( qm.bid_price_denominator_indicator() );
		BOOST_CHECK_NO_THROW( qm.offer_price_denominator_indicator() );
		BOOST_CHECK_EQUAL( qm.security_symbol(), "\0" );
		BOOST_CHECK_EQUAL( qm.bid_price(), 0 );
		BOOST_CHECK_EQUAL( qm.bid_volume(), 0 );
		BOOST_CHECK_EQUAL( qm.offer_price(), 0 );
		BOOST_CHECK_EQUAL( qm.offer_volume(), 0 );
		BOOST_CHECK_EQUAL( qm.minute(), 0 );
		BOOST_CHECK_EQUAL( qm.bid_price_denominator_indicator(), "\0" );
		BOOST_CHECK_EQUAL( qm.offer_price_denominator_indicator(), "\0" );
	}
	{
		quote_message qm;
		std::stringstream test_stream;

		char minute = 48;
		qm.set_minute() = static_cast<boost::uint32_t> ( minute ) - 48; 

		BOOST_CHECK_EQUAL( qm.minute(), 0 );
	}
}
