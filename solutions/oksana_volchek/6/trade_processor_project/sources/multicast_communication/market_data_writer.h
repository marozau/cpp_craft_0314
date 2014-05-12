#ifndef _MULTICAST_COMMUNICATION_MARKET_DATA_WRITER_H_
#define _MULTICAST_COMMUNICATION_MARKET_DATA_WRITER_H_

#include <fstream>
#include <boost\thread.hpp>

#include "market_data_processor.h"
#include "trade_message.h"
#include "quote_message.h"

namespace multicast_communication
{
	class market_data_writer : public market_data_processor
	{
		friend class data_receiver;

		std::ofstream & out_;

		void new_trade( const trade_message_ptr & msg);
		void new_quote( const quote_message_ptr & msg);

	public:
		explicit market_data_writer(std::ofstream & out);
		~market_data_writer();

	};
}

#endif // _MULTICAST_COMMUNICATION_MARKET_DATA_WRITER_H_