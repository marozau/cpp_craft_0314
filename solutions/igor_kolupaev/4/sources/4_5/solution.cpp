#include <algorithm>
#include <boost\thread.hpp>
#include <stdexcept>

#include "solution.h"

boost::mutex task4_5::solution::min_max_mutex;

task4_5::solution::solution( const data_type& data ): 
	data_( data ),
	min_( std::numeric_limits< int >().max() ),
	max_( std::numeric_limits< int >().min() )
{
	do_calc_();
}

void task4_5::solution::do_calc_()
{
	if( data_.size() == 0 )
	{
		min_ = 0;
		max_ = 0;
		return;
	}

	boost::thread_group calculators;

	int i = 0;
	for( auto it = data_.cbegin(); it != data_.cend(); it++ )
	{
		boost::thread *t = new boost::thread( &solution::do_calc_vector_, this, &(*it) );
		calculators.add_thread( t );
	}

	calculators.join_all();
}

void task4_5::solution::do_calc_vector_( const data_item_t *data )
{
	if( data->size() == 0 )
	{
		return;
	}

	int min = std::numeric_limits< int >().max();
	int max = std::numeric_limits< int >().min();

	for( data_item_t_i it = data->cbegin(); it != data->cend(); ++it )
	{
		min = std::min( min, *it );
		max = std::max( max, *it );
	}

	boost::mutex::scoped_lock lock( min_max_mutex );

	min_ = std::min( min_, min );
	max_ = std::max( max_, max );
}

int task4_5::solution::get_min() const
{
	return min_;
}

int task4_5::solution::get_max() const
{
	return max_;
}
