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
}

void task4_5:: solution:: create_thr( const data_type& data) 
{
	boost::thread_group tg;
	for( size_t i = 1; i < data.size(); ++i )
			tg.create_thread( boost::bind( &solution::process, this , boost::ref(data[i]) ) );

		tg.join_all();
}

void task4_5:: solution::process(const std::vector <int> &data_one ) 
{
	
	for (std::vector <int> :: const_iterator iv = data_one.begin()+1; iv!=data_one.end(); iv++)
		{
			if(*iv<min_ )
			{
				boost::mutex::scoped_lock lock(mtx_);
				min_=*iv;
			}

			if(*iv>max_ )
			{
				boost::mutex::scoped_lock lock( mtx_ );
				max_=*iv;
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
