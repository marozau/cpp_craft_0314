#ifndef AGGREGATOR
#define AGGREGATOR

#include <string>
#include "thread_safe_queue.h"
#include "message_types.h"
#include <boost\function.hpp>
#include "converter.h"

namespace multicast_communication
{
	class aggregator
	{
		thread_safe_queue<std::string> quote_data;
		thread_safe_queue<std::string> trade_data;

	public:
		void SaveOne(std::string, message_type);

		template<class T> 
		void StartOutput(boost::function<void(T)> output_f)
		{

		}
	};
}

#endif //AGGREGATOR