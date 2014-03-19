#include <set>

#include "market_message_filter.h"
#include "market_message.h"

market_message_filter::market_message_filter(): _current_time( 0 )
{
	_good_types.insert( MARKET_OPEN );
	_good_types.insert( TRADE );
	_good_types.insert( QUOTE );
	_good_types.insert( MARKET_CLOSE );
}

bool market_message_filter::is_up_to_date( const binary_reader::market_message& message, uint32_t delay )
{
	return _current_time < message.time() + delay;
}

bool market_message_filter::is_type_ok( const binary_reader::market_message& message )
{
	return _good_types.count( message.type() ) > 0;
}

void market_message_filter::update_time( const binary_reader::market_message& message )
{
	if( _current_time < message.time() )
	{
		_current_time = message.time();
	}
}

uint32_t market_message_filter::current_time() const
{
	return _current_time;
}

