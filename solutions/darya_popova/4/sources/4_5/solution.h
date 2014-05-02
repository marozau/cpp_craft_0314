#ifndef _TASK4_5_SOLUTION_H_
#define _TASK4_5_SOLUTION_H_

#include <vector>
#include <set>
#include <boost\thread.hpp>

namespace task4_5
{
	typedef std::vector< std::vector< int > > data_type;

	class solution
	{
		boost::mutex mtx_;
		int min_, max_;
		void create_thr( const data_type& data );
		void process(const std::vector<int>&);
	public:
		explicit solution( const data_type& data );
		int get_min() const;
		int get_max() const;
	};
}

#endif // _TASK4_5_SOLUTION_H_

