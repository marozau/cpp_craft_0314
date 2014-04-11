#include "solution.h"
#include <algorithm>

task4_5::solution::solution( const data_type& data ):size_of_data_( data.size() )
{
	if( size_of_data_ == 0 )
		return;
	
	data_ptr_ = &data;
	curr_numb_ = 0;
	
	for( size_t i = 0; i < threads_count_; i++ )
	{
		th_gr_.create_thread( boost::bind( &task4_5::solution::sorting_data, this  ) );
	}

	th_gr_.join_all();

	min_elem_ = vect_of_min_[0];
	max_elem_ = vect_of_max_[0];
	size_t size = vect_of_min_.size();
	for( size_t i = 0; i < size; i++ )
	{
		if( vect_of_min_[i] < min_elem_ )
			min_elem_ = vect_of_min_[i];
		if( vect_of_max_[i] > max_elem_ )
			max_elem_ = vect_of_max_[i];
	}
}

int task4_5::solution::get_min() const
{
	if( size_of_data_ == 0 )
		return 0;
	return min_elem_;
}
int task4_5::solution::get_max() const
{
	if( size_of_data_ == 0 )
		return 0;
	return max_elem_;
}

void task4_5::solution::sorting_data()
{
	while( true )
	{
		std::vector< int > curr_vect;
		{
			boost::mutex::scoped_lock lock( mtx_ );
			{
				if( curr_numb_ == size_of_data_ )
					return;
				curr_vect = (*data_ptr_)[curr_numb_];
				curr_numb_++;
			}
		}
		int curr_min = curr_vect[0], curr_max = curr_vect[0];
		size_t size = curr_vect.size();
		for( size_t i = 0; i < size; i++ )
		{
			if( curr_vect[i] < curr_min )
				curr_min = curr_vect[i];
			if( curr_vect[i] > curr_max )
				curr_max = curr_vect[i];
		}
		{
			boost::mutex::scoped_lock lock( mtx_ );
			{
				vect_of_min_.push_back( curr_min );
				vect_of_max_.push_back( curr_max );
			}
		}
	}
}
