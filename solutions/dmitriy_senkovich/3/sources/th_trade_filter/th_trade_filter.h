#ifndef _th_trade_filter_
#define _th_trade_filter_

#include "trade_filter.h"

#include <boost/thread.hpp>

namespace th_trade_filter
{
	class th_trade_filter
	{
		trade_filter::trade_filter temp;
		boost::mutex mtx;
		boost::thread_group th_gr;
		static size_t id;
		static const size_t thread_count = 4;
		static const unsigned file_count = 1000;

	public:
		explicit th_trade_filter();
		void set_threads_and_run();
		void process();
	};
}

#endif