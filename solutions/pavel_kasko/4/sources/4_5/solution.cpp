#include "solution.h"
#include <limits>

task4_5::solution::solution( const data_type& data ) : data_size(data.size())
{
	if(data_size == 0)
		return;

	boost::thread_group threads;

	for(int i = 0; i < data_size; ++i)
	{
		threads.create_thread(boost::bind(&task4_5::solution::DoWork, this, data[i]));
	}

	threads.join_all();
}

void task4_5::solution::DoWork(const std::vector<int>& inputVector)
{
	const std::size_t size = inputVector.size();
	int max = std::numeric_limits<int>::min();
	int min = std::numeric_limits<int>::max();
	
	for(int i = 0; i < size; ++i)
	{
		max = std::max(max, inputVector[i]);
		min = std::min(min, inputVector[i]);
	}

	SaveMinMax(min, max);
}

void task4_5::solution::SaveMinMax(int min, int max)
{
	boost::mutex::scoped_lock lock(mtx);

	min_res.push_back(min);
	max_res.push_back(max);
}

int task4_5::solution::get_min() const
{
	if(data_size != 0)
	{
		std::size_t size = min_res.size();
		int min = std::numeric_limits<int>::max();
		
		for (int i = 0; i < size; ++i)
			min = std::min(min, min_res[i]);

		return min;
	}
	return 0;
}
int task4_5::solution::get_max() const
{
	if(data_size != 0)
	{
		std::size_t size = max_res.size();
		int max = std::numeric_limits<int>::min();
		
		for (int i = 0; i < size; ++i)
			max = std::max(max, max_res[i]);

		return max;
	}
	return 0;
}
