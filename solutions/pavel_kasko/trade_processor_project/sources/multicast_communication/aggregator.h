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
		
		void QuoteOutput();
		void TradeOutput();
	public:
		aggregator();

		void SaveOne(std::string, message_type);
		void StartOutput();
		void StopOutput();
	};
}

#endif //AGGREGATOR