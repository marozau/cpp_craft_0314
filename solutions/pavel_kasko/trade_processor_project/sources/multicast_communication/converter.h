#ifndef CONVERTER
#define CONVERTER

#include <string>
#include "quote_message.h"
#include "trade_message.h"
#include "boost\function.hpp"
#include "market_data_processor_derived.h"

namespace multicast_communication
{
	class converter
	{
		const char SOH;
		const char US;
		const char ETX;

		market_data_processor_derived dp;

		quote_message* GetShortQuoteMessage(std::string&, size_t&);
		quote_message* GetLongQuoteMessage(std::string&, size_t&);
		trade_message* GetShortTradeMessage(std::string&, size_t&);
		trade_message* GetLongTradeMessage(std::string&, size_t&);
	public:
		converter();

		void ConvertToQuote(std::string&, boost::function<void(quote_message_ptr)>);
		void ConvertToTrade(std::string&, boost::function<void(trade_message_ptr)>);
	};

}
#endif //CONVERTER