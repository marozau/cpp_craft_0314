#ifndef _TASK4_5_SOLUTION_H_
#define _TASK4_5_SOLUTION_H_

#include <vector>
#include <boost/thread.hpp>

namespace task4_5
{
	typedef std::vector< std::vector< int > > data_type;

	class solution
	{
		const data_type* ptrData_;
		size_t dataSize_;
		int min_;
		int max_;
		
		boost::mutex mutex_;
		boost::thread_group threads_;

		int findFirstNonEmpty(const data_type & myVector);
		void findLocalMinAndMax(const std::vector<int> & myVector);

	public:
		explicit solution( const data_type& data );
		int get_min() const;
		int get_max() const;
	};
}

#endif // _TASK4_5_SOLUTION_H_

