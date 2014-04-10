#ifndef _th_small_buffer_
#define _th_small_buffer_

#include "small_buffer.h"

#include <boost/thread.hpp>

namespace th_small_buffer
{
	class th_small_buffer
	{
		small_buffer::small_buffer temp;
		boost::mutex mtx;
		boost::thread_group th_gr;
		static size_t id;
		static const size_t thread_count = 4;
		static const unsigned file_count = 1000;

	public:
		explicit th_small_buffer();
		void set_threads_and_run();
		void process();
	};
}

#endif