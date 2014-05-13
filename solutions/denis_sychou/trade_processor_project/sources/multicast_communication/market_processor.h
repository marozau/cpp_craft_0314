#ifndef _MULTICAST_COMMUNICATION_MARKET_PROCESSOR_H_
#define _MULTICAST_COMMUNICATION_MARKET_PROCESSOR_H_

#include "market_data_processor.h"
#include "quote_message.h"
#include "trade_message.h"

#include <string>
#include <fstream>

#include <boost\shared_ptr.hpp>
#include <boost\function.hpp>
#include <boost\thread.hpp>
#include <boost\bind.hpp>

namespace multicast_communication
{
	class processor : market_data_processor
	{
		std::ofstream out;

		const static char SOH = 0x01
						  , EOT = 0x03
						  , US = 0x1F;

		boost::mutex output_mtx;
		trade_callback_type trade_callback;
		quote_callback_type quote_callback;

	public:
		explicit processor() {}
		explicit processor( std::string filename );
		explicit processor( trade_callback_type trade_callback_, quote_callback_type quote_callback_ ) 
			: trade_callback( trade_callback_ )
			, quote_callback( quote_callback_ )
		{ }
		virtual ~processor();

		void parse( std::string& message, message_type type );

		virtual void new_trade( const trade_message_ptr& );
		virtual void new_quote( const quote_message_ptr& );
	};

	typedef boost::shared_ptr< processor > processor_ptr;
}

#endif // _MULTICAST_COMMUNICATION_MARKET_DATA_PROCESSOR_H_