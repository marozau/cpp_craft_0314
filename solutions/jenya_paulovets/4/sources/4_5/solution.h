#ifndef _TASK4_5_SOLUTION_H_
#define _TASK4_5_SOLUTION_H_

#include <vector>
#include <boost/thread.hpp>

namespace task4_5
{
	typedef std::vector< std::vector< int > > data_type;
	typedef std::vector< int > vect;

	class solution
	{
		boost::mutex mutex;
		int max;
		int min;

		void search_max(const vect &v);
		void search_min(const vect &v);

	public:
		explicit solution(const data_type& data );
		int get_min() const;
		int get_max() const;
	};
}

#endif // _TASK4_5_SOLUTION_H_


