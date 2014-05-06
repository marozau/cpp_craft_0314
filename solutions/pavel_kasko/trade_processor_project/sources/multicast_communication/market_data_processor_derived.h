#ifndef _MARKET_DATA_PROCESSOR_H_DERIVED
#define _MARKET_DATA_PROCESSOR_H_DERIVED

#include "market_data_processor.h"

namespace multicast_communication
{
	class market_data_processor_derived : public market_data_processor
	{
	public:
		explicit market_data_processor_derived();
		virtual ~market_data_processor_derived();
	private:
		void new_trade(const trade_message_ptr&);
		void new_quote(const quote_message_ptr&);
		void new_trade(const std::string);
		void new_quote(const std::string);
	};
}

#endif // _MARKET_DATA_PROCESSOR_H_DERIVED