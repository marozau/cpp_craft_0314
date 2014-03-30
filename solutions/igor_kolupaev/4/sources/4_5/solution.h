#ifndef _TASK4_5_SOLUTION_H_
#define _TASK4_5_SOLUTION_H_

#include <vector>

namespace task4_5
{
	typedef std::vector< std::vector< int > > data_type;

	class solution
	{
	public:
		explicit solution( const data_type& data );
		int get_min() const;
		int get_max() const;
	};
}

#endif // _TASK4_5_SOLUTION_H_

