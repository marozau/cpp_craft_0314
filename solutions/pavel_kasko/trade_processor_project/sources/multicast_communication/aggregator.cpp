#include "aggregator.h"

namespace multicast_communication
{
	void aggregator::SaveOne(std::string new_data, message_type type)
	{
		if (type == message_type::QUOTE)
			quote_data.push(new_data);
		else
			trade_data.push(new_data);
	}
}
