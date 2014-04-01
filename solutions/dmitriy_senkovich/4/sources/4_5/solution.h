#ifndef _TASK4_5_SOLUTION_H_
#define _TASK4_5_SOLUTION_H_

#include <vector>
#include <boost/thread.hpp>
#include <set>

namespace task4_5
{
	typedef std::vector< std::vector< int > > data_type;

	class solution
	{
		boost::mutex mtx_;
		boost::thread_group th_gr_;
		static const size_t threads_count_ = 4;
		const data_type* data_ptr_;
		std::vector< int > vect_of_min_;
		std::vector< int > vect_of_max_;
		size_t curr_numb_;
		const size_t size_of_data_; 
		int min_elem_;
		int max_elem_;

	public:
		explicit solution( const data_type& data );
		void sorting_data();
		int get_min() const;
		int get_max() const;
	};
}

#endif // _TASK4_5_SOLUTION_H_

