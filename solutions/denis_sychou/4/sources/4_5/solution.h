#ifndef _TASK4_5_SOLUTION_H_
#define _TASK4_5_SOLUTION_H_

#include <vector>
#include <boost/thread.hpp>

namespace task4_5
{
	typedef std::vector< int > data_row;
	typedef std::vector< data_row > data_type;
		
	class solution
	{
	int _max, _min;
	data_row extreme;
	boost::mutex mtx;

	void take_extreme( data_type::const_iterator ut );

	public:
		explicit solution( const data_type& data );
		int get_min() const;
		int get_max() const;
	};
}

#endif // _TASK4_5_SOLUTION_H_

