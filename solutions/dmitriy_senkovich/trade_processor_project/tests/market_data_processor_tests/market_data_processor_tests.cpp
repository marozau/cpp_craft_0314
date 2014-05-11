 #include "test_registrator.h"

#include "market_data_processor.h"

using namespace trade_processor_project;

void tests_::market_data_processor_tests()
{
	{
		market_data_processor::datafeed datafeed;

		BOOST_CHECK_NO_THROW( datafeed.seconds );
		BOOST_CHECK_NO_THROW( datafeed.minute );
		BOOST_CHECK_NO_THROW( datafeed.stock_name );
		BOOST_CHECK_NO_THROW( datafeed.open_price );
		BOOST_CHECK_NO_THROW( datafeed.high_price );
		BOOST_CHECK_NO_THROW( datafeed.low_price );
		BOOST_CHECK_NO_THROW( datafeed.close_price );
		BOOST_CHECK_NO_THROW( datafeed.volume );
		BOOST_CHECK_NO_THROW( datafeed.bid );
		BOOST_CHECK_NO_THROW( datafeed.ask );

		BOOST_CHECK_EQUAL( datafeed.seconds, -1 );
		BOOST_CHECK_EQUAL( datafeed.minute, -1 );
		BOOST_CHECK_EQUAL( strcmp( datafeed.stock_name, "\0" ), 0 );
		BOOST_CHECK_EQUAL( datafeed.open_price, 0 );
		BOOST_CHECK_EQUAL( datafeed.high_price, 0 );
		BOOST_CHECK_EQUAL( datafeed.low_price, 0 );
		BOOST_CHECK_EQUAL( datafeed.close_price, 0 );
		BOOST_CHECK_EQUAL( datafeed.volume, 0 );
		BOOST_CHECK_EQUAL( datafeed.bid, 0 );
		BOOST_CHECK_EQUAL( datafeed.ask, 0 );
	}
	{
		quote_message_ptr qu_ptr( new quote_message );
		trade_message tm;
		tm.set_minute() = 2014;
		tm.set_price_denominator_indicator() = "A";
		tm.set_security_symbol() = "cpp";
		tm.set_trade_price() = 2014.00;
		tm.set_trade_volume() = 2014.00;
		trade_message_ptr tr_ptr( new trade_message( tm ) );
		market_data_processor::union_message um( true, tr_ptr, qu_ptr );
		trade_message_ptr trade_pointer( um.tr_msg );
		trade_message trade_msg( *um.tr_msg );
		trade_message tm_msg = *um.tr_msg;

		BOOST_CHECK_EQUAL( tm_msg.minute(), 2014 );
		BOOST_CHECK_EQUAL( strcmp( tm_msg.price_denominator_indicator().c_str(), "A" ), 0 );
		BOOST_CHECK_EQUAL( strcmp( tm_msg.security_symbol().c_str(), "cpp" ), 0 );
		BOOST_CHECK_EQUAL( tm_msg.price(), 2014.00 );
		BOOST_CHECK_EQUAL( tm_msg.volume(), 2014.00 );
	}
	{
		std::queue< market_data_processor::union_message > um_queue;
		std::queue< market_data_processor::datafeed > d_queue;
		market_data_processor processor( um_queue, d_queue );

		quote_message_ptr qu_ptr( new quote_message );
		trade_message tm;
		tm.set_minute() = 2014;
		tm.set_price_denominator_indicator() = "A";
		tm.set_security_symbol() = "cpp";
		tm.set_trade_price() = 2014.00;
		tm.set_trade_volume() = 2014.00;
		trade_message_ptr tr_ptr( new trade_message( tm ) );
		market_data_processor::union_message um( true, tr_ptr, qu_ptr );
		um_queue.push( um );

		market_data_processor::datafeed d;
		d.seconds = 2014;
		d.minute = 2014;
		d.stock_name[0] = 'c';
		d.stock_name[0] = 'p';
		d.stock_name[0] = 'p';
		d.stock_name[0] = '\0';
		d.open_price = 2014.00;
		d.high_price = 2014.00;
		d.low_price = 2014.00;
		d.close_price = 2014.00;
		d.volume = 2014.00;
		d.bid = 2014.00;
		d.ask = 2014.00;
		d_queue.push( d );

		BOOST_CHECK_EQUAL( processor.union_message_queue.empty(), false );
		BOOST_CHECK_EQUAL( processor.datafeed_queue.empty(), false );
	}
}
