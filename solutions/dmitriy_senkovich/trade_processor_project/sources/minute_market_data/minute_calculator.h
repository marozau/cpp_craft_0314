#ifndef _MARKET_CALCULATOR_H_
#define _MARKET_CALCULATOR_H_

#include "market_data_processor.h"
#include <boost/unordered_map.hpp>

namespace trade_processor_project
{
	struct market_data_processor;

	class minute_calculator
	{
		typedef boost::unordered_map< std::string, market_data_processor::datafeed > storage;

		static boost::thread start_thread_;

		storage minute_datafeed_;
		market_data_processor& processor_;
		
	public:
		static bool to_stop;
		static boost::mutex lock_to_stop;
		explicit minute_calculator( market_data_processor& processor );
		void start();
		void begin();
		void calculating( const market_data_processor::union_message& );
		void start_calculating();
		void stop_calculating();
		static void stop();
	};
}

#endif