#ifndef CONVERTER
#define CONVERTER

#include <string>
#include "quote_message.h"
#include "trade_message.h"

namespace multicast_communication
{
	class converter
	{
		const char SOH = 0x01;
		const char US = 0x1F;
		const char ETX = 0x03;

	public:
		void ConvertToQuote(std::string);
		void ConvertToTrade(std::string);
	};

}
#endif //CONVERTER