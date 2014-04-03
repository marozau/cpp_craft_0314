#include <boost\thread.hpp>

#include "solution.h"

boost::mutex task4_5::solution::mtx;
task4_5::solution::solution( const data_type& data )
{
	data_= & data;
	
}

int task4_5::solution::get_min() const
{
	boost::thread_group group_of_threads;
	for (size_t i = 0; i < data_->size(); i++){
		group_of_threads.create_thread(boost::bind( & task4_5::solution::find_min, this, i)); 		
	}

	group_of_threads.join_all();

	if (data_->size()==0) return 0;

	int cur_min = temp_[0];
	for (size_t i = 1; i < temp_.size(); i++){
		if (temp_[i]<cur_min) cur_min = temp_[i];
	}

	temp_.clear();
	return cur_min;
}
int task4_5::solution::get_max() const
{
	boost::thread_group group_of_threads;

	for (size_t i = 0; i < data_->size(); i++){
		group_of_threads.create_thread(boost::bind( & task4_5::solution::find_max, this, i)); 
	}

	group_of_threads.join_all();

	if (data_->size()==0) return 0;

	int cur_max = temp_[0];

	for (size_t i = 1; i < data_->size(); i++){
		if (temp_[i]>cur_max) cur_max = temp_[i];
	}

	temp_.clear();

	return cur_max;
}

void task4_5::solution::find_min (const size_t i) const{
	int cur  = INT_MAX;
	for (size_t j = 0; j < (*data_)[i].size(); j++){
		if ((*data_)[i][j] < cur) cur = (*data_)[i][j];
	}
	{
		boost::mutex::scoped_lock lock (task4_5::solution::mtx);
		temp_.push_back(cur);
	}
}

void task4_5::solution::find_max (const size_t i) const{
	int cur = INT_MIN;
	for (size_t j = 0; j < (*data_)[i].size(); j++){
		if ((*data_)[i][j] > cur) cur = (*data_)[i][j];
	}
	{
		boost::mutex::scoped_lock lock (task4_5::solution::mtx);
		temp_.push_back(cur);
	}
}