#include "data_feed.h"

namespace multicast_communication
{
	data_feed::data_feed(std::uint32_t minute, std::string name, double open_price) : minute(minute), open_price(open_price)
	{
		int stock_name_size = sizeof(stock_name) / sizeof(char);
		
		if(name.length() <= stock_name_size)
			strcpy(stock_name, name.c_str());
		else
			strcpy(stock_name, name.substr(0, stock_name_size).c_str());

		high_price  = 0.0;
		low_price = std::numeric_limits<double>().max();
		close_price = 0.0;
		voulme = 0.0;
		ask = 0.0;
		bid = 0.0;
	}

	void data_feed::SetHighPrice(double value)
	{
		high_price = value;
	}

	void data_feed::SetLowPrice(double value)
	{
		low_price = value;
	}

	void data_feed::SetClosePrice(double value)
	{
		close_price = value;
	}
		
	void data_feed::IncreaseVolume(double value)
	{
		voulme += value;
	}

	void data_feed::IncreaseAsk(double value)
	{
		ask += value;
	}

	void data_feed::IncreaseBid(double value)
	{
		bid += value;
	}
}