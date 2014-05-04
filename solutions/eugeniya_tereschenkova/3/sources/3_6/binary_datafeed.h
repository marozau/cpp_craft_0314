#ifndef _TASK3_6_SOLUTION_H_
#define _TASK3_6_SOLUTION_H_

#include "stock_data.h"
#include <map>
#include <boost/make_shared.hpp>
using namespace std;

namespace task3_6
{
	typedef map < string, boost::shared_ptr<std::ofstream> > map_type;
	class solution
	{
	private:
		map_type map_name_stream_;

		void close_all_ofstreams_in_map_(map_type& map_name);
	public:
		void start();
	};
}

#endif // _TASK3_6_SOLUTION_H_