#ifndef _TASK3_5_SOLUTION_H_
#define _TASK3_5_SOLUTION_H_

#include <map>
#include <boost/thread.hpp>
using namespace std;

namespace task3_5
{
	static const boost::uint32_t type_min = 0u;
	static const boost::uint32_t type_max = 100000u;
  
  	struct struct_type_param
  	{
		struct_type_param()
	  	{
			count = 0;
	  	};
	  	int count;
	  	map < boost:: uint32_t, boost:: uint32_t > map_time_size;
  	};

	class solution
	{
	private:
		boost::mutex wait_file_;
		int files_count_;
				
		void process_file_();
	
	public:
		explicit solution( const int files_count );
		void start();
	};
}

#endif // _TASK3_5_SOLUTION_H_
