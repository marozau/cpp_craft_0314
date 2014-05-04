#ifndef _TASK4_5_SOLUTION_H_
#define _TASK4_5_SOLUTION_H_

#include <vector>
#include <boost\thread.hpp>

namespace task4_5
{
	typedef std::vector< int > cont_type;
	typedef std::vector< cont_type > data_type;
	typedef cont_type::const_iterator cont_const_it;

	class solution
	{
	private:
		mutable boost::mutex wait_min_mutex_;
		mutable boost::mutex wait_max_mutex_;
		
		int min_;
		int max_;
		
		void find_min_max_(const cont_type& cont);
	
	public:
		explicit solution( const data_type& data );
		const int get_min() const;
		const int get_max() const;
	};
}

#endif // _TASK4_5_SOLUTION_H_



