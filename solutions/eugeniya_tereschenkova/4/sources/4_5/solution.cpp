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
	
	for( auto it = data.cbegin(); it != data.cend(); ++it )
	{
		group_of_slave_threads.create_thread( boost::bind( &task4_5::solution::find_min_max, this, *it ));
	}
	group_of_slave_threads.join_all();
}

int task4_5::solution::get_min() const
{
	return min_;
}
int task4_5::solution::get_max() const
{
	return max_;
}

void task4_5::solution::find_min_max(cont_type& cont)
{ 
	boost::mutex::scoped_lock lock_min_and_max(task4_5::solution::wait_min_max_mutex_);
	{
		for(cont_const_it it = cont.begin(); it != cont.end(); ++it) 
		{
			const int element = *it;
			min_ = std::min( min_, element );
			max_ = std::max( max_, element );
		}
	}
}
