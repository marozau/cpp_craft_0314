#ifndef _MINUTE_MARKET_DATA_H_
#define _MINUTE_MARKET_DATA_H_

#include "multicast_communication.h"
#include "minute_calculator.h"
#include "market_data_processor.h"
#include <queue>
#include <set>

namespace trade_processor_project
{
	class minute_market_data
	{
		typedef std::pair< std::string, unsigned short > address;
		typedef std::set< std::string > filename_set;

		static boost::thread start_thread_;

		market_data_processor& processor_;

		const size_t trade_ports_amount_;
		const size_t quote_ports_amount_;
		const size_t trade_thread_size_;
		const size_t quote_thread_size_;

		const std::vector< address > trade_ports_;
		const std::vector< address > quote_ports_;


	public:
		filename_set files_to_delete;
		static bool to_stop;
		static boost::mutex lock_to_stop;
		explicit minute_market_data( const size_t, const size_t, const size_t, const size_t, const std::vector< address >&, const std::vector< address >&, market_data_processor& processor );
		void start();
		void create_data();
		void write_datafeed( market_data_processor::datafeed& );
		void stop_work();
		static void stop();
	};
}

#endif