#include <boost\thread.hpp>

#include "solution.h"


task4_5::solution::solution( const data_type& data ):data_(data)
{
	get_min_max_();
}

void task4_5::solution::get_min_max_ () const
{
	boost::thread_group group_of_threads;
	for (size_t i = 0; i < data_.size(); ++i){
		group_of_threads.create_thread(boost::bind( & task4_5::solution::find_min_max_, this, i)); 		
	}

	group_of_threads.join_all();

	if (data_.size()==0){
		min_ = 0;
		max_ = 0;
		return;
	}

	int cur_min = temp_min_[0];
	int cur_max = temp_max_[0];
	for (size_t i = 1; i < data_.size(); ++i){
		if (temp_min_[i]<cur_min) cur_min = temp_min_[i];
		if (temp_max_[i]>cur_max) cur_max = temp_max_[i];
	}

	temp_min_.clear();
	temp_max_.clear();
	min_ = cur_min;
	max_ = cur_max;
}
int task4_5::solution::get_min() const
{
	return min_;
}
int task4_5::solution::get_max() const
{
	return max_;
}

void task4_5::solution::find_min_max_ (const size_t i) const
{
	int cur_min  = INT_MAX;
	int cur_max  = INT_MIN;
	{
		boost::mutex::scoped_lock lock (mtx_data_);
		for (size_t j = 0; j < data_[i].size(); ++j){
			if (data_[i][j] < cur_min) cur_min = data_[i][j];
			if (data_[i][j] > cur_max) cur_max = data_[i][j];
		}
	}
	{
		boost::mutex::scoped_lock lock (mtx_temp_);
		temp_min_.push_back(cur_min);
		temp_max_.push_back(cur_max);
	}
}
