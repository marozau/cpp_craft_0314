#ifndef AGGREGATOR
#define AGGREGATOR

#include <string>
#include "thread_safe_queue.h"
#include "message_types.h"

namespace multicast_communication
{
	class aggregator
	{
		thread_safe_queue<std::string> quote_data;
		thread_safe_queue<std::string> trade_data;

	public:
		void SaveOne(std::string, message_type);
	};
}

#endif //AGGREGATOR