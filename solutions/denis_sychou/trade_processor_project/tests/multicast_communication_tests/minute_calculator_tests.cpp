#include "test_registrator.h"

#include <minute_calculator.h>
#include <market_processor.h>

namespace multicast_communication
{
	namespace tests_
	{
		void calculator_callback( const minute_calculator::minute_datafeed_ptr& datafeed )
		{
			BOOST_CHECK_EQUAL( datafeed->stock_name, "ACN" );
			BOOST_CHECK_EQUAL( datafeed->high_price, 779000 );
			BOOST_CHECK_EQUAL( datafeed->close_price, 779000 );
			BOOST_CHECK_EQUAL( datafeed->open_price, 779000 );
			BOOST_CHECK_EQUAL( datafeed->low_price, 779000 );
			BOOST_CHECK_EQUAL( datafeed->volume, 100 );			
			BOOST_CHECK_EQUAL( datafeed->minute, 603 );
		}
	}
}

void multicast_communication::tests_::minute_calculator_tests()
{
	{
		minute_calculator::minute_datafeed_ptr datafeed_ptr( new minute_calculator::minute_datafeed( "Test_name" ) );

		BOOST_CHECK_EQUAL( datafeed_ptr->stock_name, "Test_name" );
		BOOST_CHECK_EQUAL( datafeed_ptr->ask, 0 );
		BOOST_CHECK_EQUAL( datafeed_ptr->bid, 0 );
		BOOST_CHECK_EQUAL( datafeed_ptr->close_price, 0 );
		BOOST_CHECK_EQUAL( datafeed_ptr->high_price, 0 );
		BOOST_CHECK_EQUAL( datafeed_ptr->low_price, 0 );
		BOOST_CHECK_EQUAL( datafeed_ptr->minute, 0 );
		BOOST_CHECK_EQUAL( datafeed_ptr->open_price, 0 );
		BOOST_CHECK_EQUAL( datafeed_ptr->volume, 0 );
	}
	{
		minute_calculator::minute_calculator_ptr calculator( new minute_calculator::minute_calculator( boost::bind( &calculator_callback, _1 ) ) );

		multicast_communication::processor_ptr processor( new multicast_communication::processor( boost::bind( &minute_calculator::minute_calculator::new_trade, *calculator, _1 )
																								, boost::bind( &minute_calculator::minute_calculator::new_quote, *calculator, _1 ) ) );

		std::string msg;
		std::ifstream input( SOURCE_DIR "/tests/data/trade_tests.txt" );
		std::getline( input, msg );
		BOOST_CHECK_NO_THROW( processor->parse( msg, TRADE ) );
	}

}