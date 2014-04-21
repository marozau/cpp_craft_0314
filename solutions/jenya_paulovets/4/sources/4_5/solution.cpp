#include "solution.h"

task4_5::solution::solution(const data_type& data) : min(std::numeric_limits< int >().max()), max(std::numeric_limits< int >().min())
{
	boost::thread_group threads;

	if (!data.empty())
	{
		for (size_t i = 0; i < data.size(); i++)
		{
			threads.create_thread(boost::bind(&task4_5::solution::search_min, this, boost::ref(data[i])));
			threads.create_thread(boost::bind(&task4_5::solution::search_max, this, boost::ref(data[i])));
		}

		threads.join_all();

	}
	else
	{
		min = 0;
		max = 0;
	}
}

int task4_5::solution::get_min() const
{
	return min;
}

int task4_5::solution::get_max() const
{
	return max;
}

void task4_5::solution::search_min(const vect &subVect)
{
	if(!subVect.empty())
	{
		int locMin = subVect.at(0);

		for( vect::const_iterator it = subVect.begin() + 1; it != subVect.end(); ++it)
			if(*it < locMin) locMin = *it;

		boost::mutex::scoped_lock lock(mutex);
		{
			if(locMin < min) min = locMin;
		}
	}
}

void task4_5::solution::search_max(const vect &subVect)
{
	if(!subVect.empty())
	{
		int locMax = subVect.at(0);

		for( vect::const_iterator it = subVect.begin() + 1; it != subVect.end(); ++it)
			if(*it > locMax) locMax = *it;

		boost::mutex::scoped_lock lock(mutex);
		{
			if(locMax > max) max = locMax;
		}
	}
}

