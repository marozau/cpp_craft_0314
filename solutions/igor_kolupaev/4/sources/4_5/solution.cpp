#include <algorithm>
#include <boost\thread.hpp>
#include <stdexcept>

#include "solution.h"

boost::mutex task4_5::data_queue_iterator::queue_mutex_;

task4_5::data_queue_iterator::data_queue_iterator( const data_type& data ): data_( data ), data_it_( data.cbegin() )
{
}

task4_5::data_item_t& task4_5::data_queue_iterator::next()
{
	boost::mutex::scoped_lock lock( queue_mutex_ );

	if( data_it_ == data_.end() )
	{
		throw std::logic_error("end");
	}

	data_item_t item = *data_it_;
	data_it_++;

	return item;
}

boost::mutex task4_5::solution::min_max_mutex;

task4_5::solution::solution( const data_type& data ): 
	data_( data ),
	min_( std::numeric_limits< int >().max() ),
	max_( std::numeric_limits< int >().min() )
{
	do_calc();
}

void task4_5::solution::do_calc()
{
	if( data_.size() == 0 )
	{
		min_ = 0;
		max_ = 0;
		return;
	}

	boost::thread_group calculators;

	for( auto it = data_.cbegin(); it != data_.cend(); it++ )
	{
		data_item_t d = *it;

		do_calc_vector( *it );

		//boost::thread *t = new boost::thread( &solution::do_calc_vector, this, d );
		//t->start_thread();
		//calculators.add_thread( t );
	}

	calculators.join_all();
}

void task4_5::solution::do_calc_vector( const data_item_t &data )
{
	if( data.size() == 0 )
	{
		return;
	}

	int min = std::numeric_limits< int >().max();
	int max = std::numeric_limits< int >().min();

	for( data_item_t_i it = data.cbegin(); it != data.cend(); ++it )
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
