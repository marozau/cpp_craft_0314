#ifndef _TASK4_5_SOLUTION_H_
#define _TASK4_5_SOLUTION_H_

#include <vector>
#include <boost\thread.hpp>

namespace task4_5
{
	typedef std::vector< std::vector< int > > data_type;

	class solution
	{
		mutable std::vector < int > temp_; 
		const task4_5::data_type *  data_;
		static boost::mutex mtx;
	public:
		explicit solution( const data_type& data );
		int get_min() const;
		int get_max() const;
		void find_min(const size_t i) const;
		void find_max(const size_t i) const;
	};
}

#endif // _TASK4_5_SOLUTION_H_

