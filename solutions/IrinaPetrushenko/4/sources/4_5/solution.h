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
		static boost::mutex mtx;
		mutable int min_;
		mutable int max_;
	public:
		explicit solution( const data_type& data );
		solution * operator = (solution const & sol);
		int get_min() const;
		int get_max() const;
		void get_min_max () const;
		void find_min_max (const size_t i) const;
	};
}

#endif // _TASK4_5_SOLUTION_H_

