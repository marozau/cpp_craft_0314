#include <set>

#include "market_message_filter.h"
#include "market_message.h"

market_message_filter::market_message_filter(): current_time_( 0 )
{
	good_types_.insert( MARKET_OPEN );
	good_types_.insert( TRADE );
	good_types_.insert( QUOTE );
	good_types_.insert( MARKET_CLOSE );
}

bool market_message_filter::is_up_to_date( const binary_reader::market_message& message, uint32_t delay ) const
{
	return current_time_ < message.time() + delay;
}

bool market_message_filter::is_type_ok( const binary_reader::market_message& message ) const
{
	return good_types_.count( message.type() ) > 0;
}

void market_message_filter::update_time( const binary_reader::market_message& message )
{
	if( current_time_ < message.time() )
	{
		current_time_ = message.time();
	}
}

uint32_t market_message_filter::current_time() const
{
	return current_time_;
}

