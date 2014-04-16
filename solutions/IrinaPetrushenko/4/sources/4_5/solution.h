#ifndef _TASK4_5_SOLUTION_H_
#define _TASK4_5_SOLUTION_H_

#include <vector>
#include <boost\thread.hpp>

namespace task4_5
{
	typedef std::vector< std::vector< int > > data_type;

	class solution
	{
		mutable std::vector < int > temp_min_; 
		mutable std::vector < int > temp_max_; 
		const task4_5::data_type &  data_;
		mutable boost::mutex mtx_data_;
		mutable boost::mutex mtx_temp_;
		mutable int min_;
		mutable int max_;
		void get_min_max_ () const;
		void find_min_max_ (const size_t i) const;
	public:
		explicit solution( const data_type& data );
		int get_min() const;
		int get_max() const;
	};
}

#endif // _TASK4_5_SOLUTION_H_

