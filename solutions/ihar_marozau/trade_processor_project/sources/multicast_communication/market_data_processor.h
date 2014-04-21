#ifndef _MULTICAST_COMMUNICATION_MARKET_DATA_PROCESSOR_H_
#define _MULTICAST_COMMUNICATION_MARKET_DATA_PROCESSOR_H_

#include <trade_message.h>
#include <quote_message.h>

namespace multicast_communication
{
	class market_data_processor
	{
		friend class market_data_receiver; // please insert here your processing class 
	public:
		explicit market_data_processor(){}
		virtual ~market_data_processor(){}
	private:
		virtual void new_trade( const trade_message_ptr& ) = 0;
		virtual void new_quote( const quote_message_ptr& ) = 0;
	};
}

#endif // _MULTICAST_COMMUNICATION_MARKET_DATA_PROCESSOR_H_
