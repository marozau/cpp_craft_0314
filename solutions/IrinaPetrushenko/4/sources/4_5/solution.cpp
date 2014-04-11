#include <boost\thread.hpp>

#include "solution.h"

boost::mutex task4_5::solution::mtx;

task4_5::solution::solution( const data_type& data ):data_(data)
{
	get_min_max();
}

task4_5::solution * task4_5::solution::operator = (task4_5::solution const & sol){
	if (&sol==this)
		std::cerr<<"not logical operation"<<std::endl;
	return this;	
}
void task4_5::solution::get_min_max () const
{
	boost::thread_group group_of_threads;
	for (size_t i = 0; i < data_.size(); ++i){
		group_of_threads.create_thread(boost::bind( & task4_5::solution::find_min_max, this, i)); 		
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

void task4_5::solution::find_min_max (const size_t i) const{
	int cur_min  = INT_MAX;
	int cur_max  = INT_MIN;
	for (size_t j = 0; j < data_[i].size(); ++j){
		if (data_[i][j] < cur_min) cur_min = data_[i][j];
		if (data_[i][j] > cur_max) cur_max = data_[i][j];
	}
	{
		boost::mutex::scoped_lock lock (task4_5::solution::mtx);
		temp_min_.push_back(cur_min);
		temp_max_.push_back(cur_max);
	}
}
