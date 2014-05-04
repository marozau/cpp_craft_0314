#include "solution.h"
#include <limits>

task4_5::solution::solution( const data_type& data ) : data_size(data.size())
{
	if(data_size == 0)
		return;

	max = std::numeric_limits<int>::min();
	min = std::numeric_limits<int>::max();

	boost::thread_group threads;

	for(int i = 0; i < data_size; ++i)
	{
		threads.create_thread(boost::bind(&task4_5::solution::DoWork, this, boost::ref(data[i])));
	}

	threads.join_all();
}

void task4_5::solution::DoWork(const std::vector<int>& inputVector)
{
	const std::size_t size = inputVector.size();
	
	int local_max = std::numeric_limits<int>::min();
	int local_min = std::numeric_limits<int>::max();

	for(int i = 0; i < size; ++i)
	{
		local_max = std::max(local_max, inputVector[i]);
		local_min = std::min(local_min, inputVector[i]);
	}

	SaveMinMax(local_min, local_max);
}

void task4_5::solution::SaveMinMax(int min_, int max_)
{
	boost::mutex::scoped_lock lock(mtx);

	min = std::min(min, min_);
	max = std::max(max, max_);
}

int task4_5::solution::get_min()
{
	return data_size != 0 ? min : 0;
}
int task4_5::solution::get_max()
{
	return data_size != 0 ? max : 0;
}
