#include "market_data_processor_derived.h"
#include <string>

namespace multicast_communication
{
	void market_data_processor_derived::new_quote(const std::string str)
	{
		std::cout << "new_quote " << str << std::endl;
	}

	void market_data_processor_derived::new_trade(const std::string str)
	{
		std::cout << "new_trade " << str << std::endl;
	}
}