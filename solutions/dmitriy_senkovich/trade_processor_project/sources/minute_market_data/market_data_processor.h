#ifndef _MARKET_DATA_PROCESSOR_H_
#define _MARKET_DATA_PROCESSOR_H_

#include <queue>
#include "quote_message.h"
#include "trade_message.h"
#include <boost/thread.hpp>

namespace trade_processor_project
{
	typedef boost::shared_ptr< trade_message > trade_message_ptr;
	typedef boost::shared_ptr< quote_message > quote_message_ptr;

	struct market_data_processor
	{
		struct union_message
		{
			bool trade;
			trade_message_ptr tr_msg;
			quote_message_ptr qu_msg;
			explicit union_message();
			explicit union_message( bool, trade_message_ptr, quote_message_ptr );
		};

		struct datafeed
		{
			boost::uint32_t seconds;
			boost::uint32_t minute;
			char* stock_name;
			double open_price;
			double high_price;
			double low_price;
			double close_price;
			double volume;
			double bid;
			double ask;
			explicit datafeed();
			explicit datafeed( const datafeed& );
			const datafeed& operator=( const datafeed& );
			~datafeed();
		};

		std::queue<union_message>& union_message_queue;
		std::queue<datafeed>& datafeed_queue;

		static boost::mutex lock_union_message_queue_access;
		static boost::mutex lock_datafeed_queue_access;
		static boost::condition_variable union_message_queue_cond_var;
		static boost::condition_variable datafeed_queue_cond_var;

		explicit market_data_processor( std::queue<union_message>&, std::queue<datafeed>& );
	};
}

#endif