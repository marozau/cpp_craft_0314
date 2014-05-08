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
		const char SOH = 0x01;
		const char US = 0x1F;
		const char ETX = 0x03;

		market_data_processor_derived dp;

		void QuoteOut(boost::function<void(quote_message_ptr)>);
		void TradeOut(boost::function<void(trade_message_ptr)>);
	public:
		converter();

		void ConvertToQuote(std::string);
		void ConvertToTrade(std::string);
	};

}
#endif //CONVERTER