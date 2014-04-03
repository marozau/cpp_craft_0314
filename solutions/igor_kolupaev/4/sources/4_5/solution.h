#ifndef _TASK4_5_SOLUTION_H_
#define _TASK4_5_SOLUTION_H_

#include <vector>
#include <boost\thread.hpp>

namespace task4_5
{
	typedef std::vector< int > data_item_t;
	typedef data_item_t::const_iterator data_item_t_i;
	typedef std::vector< data_item_t > data_type;

	class data_queue_iterator
	{
		const data_type &data_;
		static boost::mutex queue_mutex_;
		std::vector< data_item_t >::const_iterator data_it_;

	public:
		
		data_queue_iterator( const data_type& data );
		data_item_t& next();
	};

	class solution
	{
		const data_type &data_;

		int min_;
		int max_;

		static boost::mutex min_max_mutex;

		void do_calc();
		void do_calc_vector( const data_item_t &data );

	public:
		explicit solution( const data_type& data );
		int get_min() const;
		int get_max() const;
	};
}

#endif // _TASK4_5_SOLUTION_H_

