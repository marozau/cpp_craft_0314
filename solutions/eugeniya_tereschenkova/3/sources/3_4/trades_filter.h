#ifndef _TASK3_4_SOLUTION_H_
#define _TASK3_4_SOLUTION_H_

#include <boost\thread.hpp>

namespace task3_4
{
	static const boost::uint32_t type_min = 1u;
	static const boost::uint32_t type_max = 4u;
	static const long long N = static_cast<long long>(pow(10.0,16.0));

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

#endif // _TASK3_4_SOLUTION_H_
