#include "market_data_processor.h"

using namespace trade_processor_project;

boost::mutex market_data_processor::lock_union_message_queue_access;
boost::mutex market_data_processor::lock_datafeed_queue_access;
boost::condition_variable market_data_processor::union_message_queue_cond_var;
boost::condition_variable market_data_processor::datafeed_queue_cond_var;

market_data_processor::datafeed::datafeed()
	:seconds( -1 )
	,minute( -1 )
	,stock_name( new char[16] )
	,open_price( 0 )
	,high_price( 0 )
	,low_price( 0 )
	,close_price( 0 )
	,volume( 0 )
	,bid( 0 )
	,ask( 0 )
{
	stock_name[0] = '\0';
}
market_data_processor::datafeed::~datafeed()
{
	delete []stock_name;
}
market_data_processor::datafeed::datafeed( const datafeed& d )
{
	seconds = d.seconds;
	minute = d.minute;
	stock_name = new char[16];
	size_t i = 0;
	for( ; d.stock_name[i] != '\0'; i++ )
		stock_name[i] = d.stock_name[i];
	stock_name[i] = '\0';
	open_price = d.open_price;
	high_price = d.high_price;
	low_price = d.low_price;
	close_price = d.close_price;
	volume = d.volume;
	bid = d.bid;
	ask = d.ask;
}
const market_data_processor::datafeed& market_data_processor::datafeed::operator=( const datafeed& d )
{
	if( &d == this )
		return *this;
	seconds = d.seconds;
	minute = d.minute;
	delete []stock_name;
	stock_name = new char[16];
	size_t i = 0;
	for( ; d.stock_name[i] != '\0'; i++ )
		stock_name[i] = d.stock_name[i];
	stock_name[i] = '\0';
	open_price = d.open_price;
	high_price = d.high_price;
	low_price = d.low_price;
	close_price = d.close_price;
	volume = d.volume;
	bid = d.bid;
	ask = d.ask;
	return *this;
}
market_data_processor::union_message::union_message()
{
}
market_data_processor::union_message::union_message( bool tr, trade_message_ptr tm, quote_message_ptr qm )
{
	if( tr )
	{
		trade = true;
		tr_msg = tm;
	}
	else
	{
		trade = false;
		qu_msg = qm;
	}
}
market_data_processor::market_data_processor( std::queue< market_data_processor::union_message >& um_queue, std::queue<datafeed>& d_queue )
	:union_message_queue( um_queue )
	,datafeed_queue( d_queue )
{
}