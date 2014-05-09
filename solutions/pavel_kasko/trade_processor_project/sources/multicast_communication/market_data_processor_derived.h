#ifndef _MARKET_DATA_PROCESSOR_H_DERIVED
#define _MARKET_DATA_PROCESSOR_H_DERIVED

#include "market_data_processor.h"
#include <boost\thread.hpp>
#include <fstream>

namespace multicast_communication
{
	class market_data_processor_derived : public market_data_processor
	{
	public:
		explicit market_data_processor_derived();
		virtual ~market_data_processor_derived();
			
		void new_trade(const trade_message_ptr&);
		void new_quote(const quote_message_ptr&);
	
	private:
		const std::string file_name;

		boost::mutex locker;
		std::ofstream output;
		void write_data(std::stringstream&);
	};
}

#endif // _MARKET_DATA_PROCESSOR_H_DERIVED
