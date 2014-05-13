#include "minute_calculator.h"
#include <boost\lexical_cast.hpp>

minute_calculator::minute_calculator::~minute_calculator()
{
	for( datafeed_storage_type::const_iterator it = data.cbegin(); it != data.cend(); ++it )
		handler( it->second );
}

void minute_calculator::minute_calculator::new_trade( const multicast_communication::trade_message_ptr& msg )
{
	std::string stock_name = msg->security_symbol();

	if( data.count( stock_name ) != 0 && data[ stock_name ]->minute > msg->minute() )
		return;

	if(  data.count( stock_name ) != 0 && data[ stock_name ]->minute == msg->minute() )
	{
		data[ stock_name ]->high_price = std::max( data[ stock_name ]->high_price, msg->price() );
		data[ stock_name ]->low_price = std::min( data[ stock_name ]->low_price, msg->price() );
		data[ stock_name ]->volume += msg->volume();
		data[ stock_name ]->close_price = msg->minute();
	}
	else
	{
		if( data.count( stock_name ) != 0 )
		{
			handler( data[ stock_name ] );
			data.erase( stock_name );
		}
		minute_datafeed_ptr temp( new minute_datafeed( stock_name ) );
		temp->open_price = temp->high_price = temp->close_price = temp->low_price = msg->price();
		temp->volume = msg->volume();
		temp->minute = msg->minute();
		data.insert( std::make_pair( stock_name, temp ) );
	}

}

void minute_calculator::minute_calculator::new_quote( const multicast_communication::quote_message_ptr& msg )
{
	std::string stock_name = msg->security_symbol();

	if( data.count( stock_name ) != 0 && data[ stock_name ]->minute > msg->minute() )
		return;

	if(  data.count( stock_name ) != 0 && data[ stock_name ]->minute == msg->minute() )
	{
		data[ stock_name ]->ask += msg->offer_volume();
		data[ stock_name ]->bid += msg->bid_volume();
	}
	else
	{
		if( data.count( stock_name ) != 0 )
		{
			handler( data[ stock_name ] );
			data.erase( stock_name );
		}
		minute_datafeed_ptr temp( new minute_datafeed( stock_name ) );
		temp->ask = msg->offer_volume();
		temp->bid = msg->bid_volume();
		data.insert( std::make_pair( stock_name, temp ) );
	}
}