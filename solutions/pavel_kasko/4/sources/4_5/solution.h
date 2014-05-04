#ifndef _TASK4_5_SOLUTION_H_
#define _TASK4_5_SOLUTION_H_

#include <vector>
#include <boost\thread.hpp>

namespace task4_5
{
	typedef std::vector< std::vector< int > > data_type;

	class solution
	{
		boost::mutex mtx;

		const std::size_t data_size;
		int min;
		int max;
		void DoWork(const std::vector<int>& inputVector);
		void SaveMinMax(int min, int max);
	public:
		explicit solution( const data_type& data );
		int get_min();
		int get_max();
	};
}

#endif // _TASK4_5_SOLUTION_H_

