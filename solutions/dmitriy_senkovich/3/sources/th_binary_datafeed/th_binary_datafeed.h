#ifndef _th_binary_datafeed_
#define _th_binary_datafeed_

#include "stock_data.h"

#include <boost/thread.hpp>
#include <boost/unordered_map.hpp>
#include <vector>

namespace th_binary_datafeed
{
	typedef boost::unordered_map< std::string, std::vector<binary_reader::stock_data> > data_map;
	typedef std::vector<binary_reader::stock_data>::iterator msg_iter;

	class th_binary_datafeed
	{
		boost::mutex mtx_;
		boost::thread_group th_gr_;
		static const size_t thread_count_ = 4ul;
		data_map data_storage_;
		data_map::iterator data_iter_;

	public:
		explicit th_binary_datafeed();
		void read_set_threads_and_run_process();
		void set_threads_and_run_process();
		void process();
	};
}

#endif