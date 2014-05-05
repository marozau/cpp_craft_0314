#include "solution.h"

task4_5::solution::solution( const data_type& data ): min_( 0 ), max_( 0 )
{
	if(data.empty())
	{
		return;
	}
	min_ = std::numeric_limits< int >().max();
	max_ = std::numeric_limits< int >().min();
	
	boost::thread_group group_of_slave_threads;
	for (size_t i = 0; i < data.size(); ++i)
	{
		group_of_slave_threads.create_thread( boost::bind( &task4_5::solution::find_min_max_, this, boost::ref(data[i])));
	}
	group_of_slave_threads.join_all();
}

const int task4_5::solution::get_min() const
{
	boost::mutex::scoped_lock lock_min(task4_5::solution::wait_min_mutex_);
	return min_;
}
const int task4_5::solution::get_max() const
{
	boost::mutex::scoped_lock lock_max(task4_5::solution::wait_max_mutex_);
	return max_;
}

void task4_5::solution::find_min_max_(const cont_type& cont)
{ 
	int max = std::numeric_limits<int>().min();
	int min = std::numeric_limits<int>().max();
	for(cont_const_it it = cont.begin(); it != cont.end(); ++it) 
	{
		const int element = *it;
		min = std::min( min, element );
		max = std::max( max, element );
	}

	boost::mutex::scoped_lock lock_max(task4_5::solution::wait_max_mutex_);
	{
		max_ = std::max( max_, max );
	}
	boost::mutex::scoped_lock lock_min(task4_5::solution::wait_min_mutex_);
	{
		min_ = std::min( min_, min );
	}
}