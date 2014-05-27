#ifndef _MULTICAST_COMMUNICATION_MINUTE_CALCULATOR_H_
#define _MULTICAST_COMMUNICATION_MINUTE_CALCULATOR_H_

#include <boost\shared_ptr.hpp>
#include <boost\cstdint.hpp>
#include <boost\unordered_map.hpp>
#include <boost\function.hpp>
#include <boost\bind.hpp>

#include <string>
#include <utility>
#include <fstream>

#include "trade_message.h"
#include "quote_message.h"

namespace minute_calculator
{
	struct minute_datafeed
	{
		boost::uint32_t minute;
		char stock_name[ 16 ];
		double open_price
			   , high_price
			   , low_price
			   , close_price
			   , volume
			   , bid
			   , ask;

		minute_datafeed() : minute( 0 )
							, open_price( 0 )
							, high_price( 0 )
							, low_price( 0 )
							, close_price( 0 )
							, volume( 0 )
							, bid( 0 )
							, ask( 0 )
		{
			stock_name[ 0 ] = '\0';
		}
		
		minute_datafeed( std::string stock_name_ ) : minute( 0 )
													, open_price( 0 )
													, high_price( 0 )
													, low_price( 0 )
													, close_price( 0 )
													, volume( 0 )
													, bid( 0 )
													, ask( 0 )
		{
			std::memcpy( stock_name, stock_name_.c_str(), stock_name_.size() );
			stock_name[ stock_name_.size() ] = '\0';
		}
	};

	typedef boost::shared_ptr< minute_datafeed > minute_datafeed_ptr;
	typedef boost::function< void( const minute_datafeed_ptr& datafeed ) > datafeed_callback_type;
	typedef boost::unordered_map< std::string, minute_datafeed_ptr > datafeed_storage_type;

	class minute_calculator
	{
		datafeed_callback_type handler;
		datafeed_storage_type data;
		
	public:
		explicit minute_calculator( datafeed_callback_type handler_ ) : handler( handler_ ) { }	
		~minute_calculator();

		void new_trade( const multicast_communication::trade_message_ptr& msg );
		void new_quote( const multicast_communication::quote_message_ptr& msg );		
	};

	typedef boost::shared_ptr< minute_calculator > minute_calculator_ptr;
}

#endif // _MULTICAST_COMMUNICATION_MINUTE_CALCULATOR_H_