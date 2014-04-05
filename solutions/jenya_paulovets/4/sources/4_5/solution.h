#ifndef _TASK4_5_SOLUTION_H_
#define _TASK4_5_SOLUTION_H_

#include <vector>
#include <boost/thread.hpp>
#include <boost/thread.hpp>

namespace task4_5
{
	typedef std::vector< std::vector< int > > data_type;
	typedef std::vector< int > vect;

	class solution
	{
		boost::mutex mutex;
		vect mins;
		vect maxs;
		data_type data;

		void search_max(vect &vect);
		void search_min(vect &vect);

	public:
		explicit solution(const data_type& data );
		int get_min();
		int get_max();
	};
}

#endif // _TASK4_5_SOLUTION_H_

