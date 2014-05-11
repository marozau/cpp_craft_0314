#ifndef MINUTE_CALCULATOR
#define MINUTE_CALCULATOR

#include<string>
#include "message_types.h"
#include "converter.h"
#include <map>
#include "data_feed.h"
#include <cstdint>
#include <chrono>
#include <ctime>
#include <boost\thread.hpp>

namespace multicast_communication
{
	class minute_calculator
	{
		typedef std::chrono::high_resolution_clock Clock;

		boost::mutex locker;

		int time_dec_dif;

		bool quote_flushed;
		bool trade_flushed;

		converter _cnv;
		std::map<std::string, data_feed*> d_feeds;

		void SaveTrade(trade_message_ptr);
		void SaveQuote(quote_message_ptr);
		std::uint32_t GetMinute(std::string);
		std::uint32_t Get1990Seconds(std::string);
	public:
		minute_calculator();
		~minute_calculator();
		void SaveOne(std::string&, message_type type);
	};
}

#endif //MINUTE_CALCULATOR
