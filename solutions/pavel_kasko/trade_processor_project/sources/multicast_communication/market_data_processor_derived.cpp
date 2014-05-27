#include "market_data_processor_derived.h"
#include <string>
#include <sstream>

namespace multicast_communication
{
	

	market_data_processor_derived::~market_data_processor_derived(){}
	market_data_processor_derived::market_data_processor_derived() : file_name("market_data.dat"){}
	
	void market_data_processor_derived::new_quote(const quote_message_ptr& quote_ptr)
	{
		std::stringstream ss;
		ss << "Q " << quote_ptr->security_symbol() << " " << quote_ptr->bid_price() 
			<< " " << quote_ptr->bid_volume() << " " << quote_ptr->offer_price() 
			<< " " << quote_ptr->offer_volume() << std::endl;
		write_data(ss);
	}

	void market_data_processor_derived::new_trade(const trade_message_ptr& trade_ptr)
	{
		std::stringstream ss;
		ss << "T " << trade_ptr->security_symbol() << " " << trade_ptr->price() 
			<< " " << trade_ptr->volume() << std::endl;
		write_data(ss);
	}

	void market_data_processor_derived::write_data(std::stringstream& line)
	{
		boost::mutex::scoped_lock lock(locker);

		output.open(BINARY_DIR + std::string("/") + file_name, std::ios::out | std::ios::app);
		
		if (!output.good())
			throw std::logic_error("Cannot open output file.");

		output << line.rdbuf();
		output.close();
	}
}