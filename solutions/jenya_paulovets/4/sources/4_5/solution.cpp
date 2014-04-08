#include "solution.h"
#include <algorithm>

bool comp(const int a, const int b)
{
	return a > b;
}

task4_5::solution::solution(const data_type& d)
{
	data_type data;

	for (size_t i = 0; i < d.size(); ++i)
	{
		data.push_back(task4_5::data_type::value_type());
		for (vect::const_iterator it = d[i].begin(); it != d[i].end(); it++)
		{
			data[i].push_back(*it);
		}
	}

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

void task4_5::solution::search_min(vect &subVect, vect &mins)
{
	boost::mutex::scoped_lock lock(mutex);

	std::sort(subVect.begin(), subVect.end());

	mins.push_back(*(subVect.begin()));
}

void task4_5::solution::search_max(vect &subVect, vect& maxs)
{
	boost::mutex::scoped_lock lock(mutex);

	std::sort(subVect.begin(), subVect.end(), comp);

	maxs.push_back(*(subVect.begin()));
}
