#include "data_feed.h"
#include <fstream>
#include <sstream>

namespace multicast_communication
{
	data_feed::data_feed(std::uint32_t minute, std::string name) : minute(minute), trade_minute(minute), quote_minure(minute)
	{
		int stock_name_size = sizeof(stock_name) / sizeof(char);
		
		if(name.length() <= stock_name_size)
			strcpy(stock_name, name.c_str());
		else
			strcpy(stock_name, name.substr(0, stock_name_size).c_str());

		open_price = 0.0;
		high_price  = 0.0;
		low_price = std::numeric_limits<double>().max();
		close_price = 0.0;
		voulme = 0.0;
		ask = 0.0;
		bid = 0.0;
	}

	void data_feed::SetMinute(std::uint32_t value)
	{
		minute = value;
	}

	void data_feed::SetQuoteMinute(std::uint32_t value)
	{
		quote_minure = value;
	}

	void data_feed::SetTradeMinute(std::uint32_t value)
	{
		trade_minute = value;
	}

	void data_feed::SetHighPrice(double value)
	{
		high_price = value;
	}

	void data_feed::SetLowPrice(double value)
	{
		low_price = value;
	}

	void data_feed::SetOpenPrice(double value)
	{
		open_price = value;
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

	double data_feed::highPrice()
	{
		return high_price;
	}

	double data_feed::lowPrice()
	{
		return low_price;
	}

	std::uint32_t data_feed::tradeMinute()
	{
		return trade_minute;
	}
	
	std::uint32_t data_feed::quoteMinure()
	{
		return quote_minure;
	}

	void data_feed::ResetTradePart()
	{
		open_price = 0.0;
		high_price  = 0.0;
		low_price = std::numeric_limits<double>().max();
		close_price = 0.0;
		voulme = 0.0;
	}

	void data_feed::ResetQuotePart()
	{
		ask = 0.0;
		bid = 0.0;
	}

	void data_feed::PrintTradePart(bool is_quote_flushed)
	{
		std::ofstream output;
		std::stringstream buf;

		if(is_quote_flushed)
		{
			std::ifstream f(BINARY_DIR + std::string("/") + stock_name + ".dat");
			buf << f.rdbuf();
			f.close();
		}

		output.open(BINARY_DIR + std::string("/") + stock_name + ".dat");

		if (!output.good())
			throw std::logic_error("Cannot open output file.");

		output << minute << " " << stock_name << " " << open_price << " " << high_price << " " << low_price << " " 
			<< close_price << " " << voulme << buf.rdbuf() << std::endl;

		output.close();
	}
	
	void data_feed::PrintQuotePart(bool is_trade_flushed)
	{
		std::ofstream output;
		if(is_trade_flushed)
			output.open(BINARY_DIR + std::string("/") + stock_name + ".dat", std::ios::app);
		else
			output.open(BINARY_DIR + std::string("/") + stock_name + ".dat");

		if (!output.good())
			throw std::logic_error("Cannot open output file.");

		output << bid << " " << ask << std::endl;

		output.close();
	}

	void data_feed::Print()
	{
		std::ofstream output;
		output.open(BINARY_DIR + std::string("/") + stock_name + ".dat");
		
		if (!output.good())
			throw std::logic_error("Cannot open output file.");

		output << minute << " " << stock_name << " " << open_price << " " << high_price << " " << low_price << " " 
			<< close_price << " " << voulme << " " << bid << " " << ask << std::endl;

		output.close();
	}
}