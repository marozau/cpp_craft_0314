#include "solution.h"
#include <algorithm>

bool comp(const int a, const int b)
{
	return a > b;
}

task4_5::solution::solution(const data_type& data)
{
	boost::thread_group threads;

	vect mins;
	vect maxs;

	if (!data.empty())
	{
		for (size_t i = 0; i < data.size(); i++)
		{
			threads.create_thread(boost::bind(&task4_5::solution::search_min, this, boost::ref(data[i]), boost::ref(mins)));
			threads.create_thread(boost::bind(&task4_5::solution::search_max, this, boost::ref(data[i]), boost::ref(maxs)));
		}

		threads.join_all();

		std::sort(mins.begin(), mins.end());
		std::sort(maxs.begin(), maxs.end(), comp);

		min = *(mins.begin());
		max = *(maxs.begin());
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

void task4_5::solution::search_min(const vect &subVect, vect &mins)
{
	boost::mutex::scoped_lock lock(mutex);

	if(!subVect.empty())
	{
		int bufMin = subVect.at(0);

		for( vect::const_iterator it = subVect.begin() + 1; it != subVect.end(); ++it)
			if(*it < bufMin) bufMin = *it;

		mins.push_back(bufMin);
	}
}

void task4_5::solution::search_max(const vect &subVect, vect& maxs)
{
	boost::mutex::scoped_lock lock(mutex);

	if(!subVect.empty())
	{
		int bufMax = subVect.at(0);

		for( vect::const_iterator it = subVect.begin() + 1; it != subVect.end(); ++it)
			if(*it > bufMax) bufMax = *it;

		maxs.push_back(bufMax);
	}
}
