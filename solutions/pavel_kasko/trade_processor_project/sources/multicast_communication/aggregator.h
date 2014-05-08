#ifndef AGGREGATOR
#define AGGREGATOR

#include <string>
#include "thread_safe_queue.h"
#include "message_types.h"
#include <boost\function.hpp>
#include "converter.h"
#include "boost\thread.hpp"

namespace multicast_communication
{
	class aggregator
	{
		bool end;

		thread_safe_queue<std::string> quote_data;
		thread_safe_queue<std::string> trade_data;

		market_data_processor_derived& md;
		
		void QuoteOutput();
		void TradeOutput();
	public:
		aggregator(market_data_processor_derived&);

		void SaveOne(std::string, message_type);
		void StartOutput();
		void StopOutput();
	};
}

#endif //AGGREGATOR