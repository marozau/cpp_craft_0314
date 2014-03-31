#include "solution.h"
#include "../../../3/sources/utility/rvref_wrapper.h"
#include <future>
#include <algorithm>
#include <numeric>
#include <utility>

std::pair<int, int> VectMinMaxFindingFunc(rvref_wrapper<task4_5::data_type::value_type> rvvect)
{
	int min = std::numeric_limits<int>().max();
	int max = std::numeric_limits<int>().min();
	task4_5::data_type::value_type vect = rvvect.get();
	for (size_t i = 0; i < vect.size(); ++i)
	{
		min = std::min(min, vect[i]);
		max = std::max(max, vect[i]);
	}
	return std::make_pair(min, max);
}

task4_5::solution::solution(const data_type& data) : min_(0), max_(0)
{
	std::vector<std::future<std::pair<int, int>>> futures;
	if (data.empty())
	{
		min_ = 0;
		max_ = 0;
	}
	else
	{
		min_ = std::numeric_limits<int>().max();
		max_ = std::numeric_limits<int>().min();
	}
	for (size_t i = 0; i < data.size(); ++i)
	{
		data_type::value_type vectOfIntegers;
		for (size_t j = 0; j < data[i].size(); ++j)
			vectOfIntegers.push_back(data[i][j]);
		futures.push_back(std::async(&VectMinMaxFindingFunc, rvref(vectOfIntegers)));
	}
	for (auto & ftr : futures)
	{
		const auto ftrAns = ftr.get();
		min_ = std::min(min_, ftrAns.first);
		max_ = std::max(max_, ftrAns.second);
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
