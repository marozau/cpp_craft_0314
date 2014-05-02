#include "solution.h"
#include <algorithm>

task4_5::solution::solution( const data_type& data )
{
	if(data.size() == 0)
	{
		max_=min_=0;
		return;
	}
	min_ = std::numeric_limits< int >().max();
	max_ = std::numeric_limits< int >().min();
	create_thr( data);

}

void task4_5:: solution:: create_thr( const data_type& data) 
{
	boost::thread_group tg;
	for( size_t i = 1; i < data.size(); ++i )
		tg.create_thread( boost::bind( &solution::process, this , boost::ref(data[i]) ) );

	tg.join_all();
	
}

void task4_5:: solution::process(const std::vector <int> &data_one) 
{
	
	if (data_one.size()!=0)
	{
		int min = std::numeric_limits< int >().max();
		int max = std::numeric_limits< int >().min();
		for (std::vector <int> :: const_iterator iv = data_one.begin(); iv!=data_one.end(); ++iv)
		{
			if(*iv < min )
			{
				min=*iv;
			}

			if(*iv>max )
			{
				max=*iv;
			}
		}
		
		{
			boost::mutex::scoped_lock lock(mtx_);
			if(max> max_)
				max_ = max;
			if(min< min_)
				min_ = min;
		}
	}
}

int task4_5::solution::get_min() const
{
	return min_;
}
int task4_5::solution::get_max() const
{
	return max_;
}
