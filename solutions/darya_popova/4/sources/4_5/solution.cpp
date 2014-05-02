#include "solution.h"

task4_5::solution::solution( const data_type& data )
{
	if(data.size() == 0)
	{
		max_=min_=0;
		return;
	}
	max_=min_=data[0][0];
	create_thr( data);
	vmax_.clear();
	vmin_.clear();
}

void task4_5:: solution:: create_thr( const data_type& data) 
{
	boost::thread_group tg;
	for( size_t i = 1; i < data.size(); ++i )
			tg.create_thread( boost::bind( &solution::process, this , boost::ref(data[i]) ) );

	tg.join_all();
	
	for (std::vector <int> :: iterator iv = vmax_.begin(); iv!=vmax_.end(); iv++)
	{
		if(*iv > max_ )
		{
			max_=*iv;
		}
	}
	for (std::vector <int> :: iterator iv = vmin_.begin(); iv!=vmin_.end(); iv++)
	{
		if(*iv < min_ )
		{
			min_=*iv;
		}
	}
		
}

void task4_5:: solution::process(const std::vector <int> &data_one) 
{
	int max, min;
	max=min= data_one[0];
	for (std::vector <int> :: const_iterator iv = data_one.begin(); iv!=data_one.end(); iv++)
	{
		if(*iv < min_ )
		{
			min_=*iv;
		}

		if(*iv>max_ )
		{
			max_=*iv;
		}
	}
	vmax_.push_back(max_);
	vmin_.push_back(min_);
}

int task4_5::solution::get_min() const
{
	return min_;
}
int task4_5::solution::get_max() const
{
	return max_;
}
