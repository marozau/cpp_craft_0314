#include "solution.h"
#include <algorithm>

task4_5::solution::solution(const data_type& data)
{
	for (size_t i = 0; i < data.size(); ++i)
	{
		this->data.push_back(task4_5::data_type::value_type());
		for (vect::const_iterator it = data[i].begin(); it != data[i].end(); it++)
		{
			this->data[i].push_back(*it);
		}
	}
}

bool comp(const int a, const int b)
{
	return a > b;
}

int task4_5::solution::get_min()
{
	boost::thread_group threads;

	if (!data.empty())
	{
		for (size_t i = 0; i < data.size(); i++)
		{
			threads.create_thread(boost::bind(&task4_5::solution::search_min, this, boost::ref(data[i])));
		}

		threads.join_all();

		std::sort(mins.begin(), mins.end());
		return *(mins.begin());
	} else
		return 0;
}
int task4_5::solution::get_max()
{
	boost::thread_group threads;

	if (!data.empty())
	{
		for (size_t i = 0; i < data.size(); i++)
		{
			threads.create_thread(boost::bind(&task4_5::solution::search_max, this, boost::ref(data[i])));
		}

		threads.join_all();

		std::sort(maxs.begin(), maxs.end(), comp);
		return *(maxs.begin());
	} else
		return 0;
}

void task4_5::solution::search_min(vect &subVect)
{

	std::sort(subVect.begin(), subVect.end());

	{
		boost::mutex::scoped_lock lock(mutex);
		mins.push_back(*(subVect.begin()));
	}
}

void task4_5::solution::search_max(vect &subVect)
{

	std::sort(subVect.begin(), subVect.end(), comp);

	{
		boost::mutex::scoped_lock lock(mutex);
		maxs.push_back(*(subVect.begin()));
	}
}
