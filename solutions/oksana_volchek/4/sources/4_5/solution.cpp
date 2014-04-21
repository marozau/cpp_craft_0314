#include "solution.h"
#include <vector>

int task4_5::solution::findFirstNonEmpty(const data_type & myVector){
	if (myVector.empty()){
		return -1;
	}
	else {
		for (int i = 0; i < myVector.size(); ++i){
			if (!myVector[i].empty()){
				return i;
			}
		}
		return -1;
	}
}

void task4_5::solution::findLocalMinAndMax(const std::vector<int> & myVector){
	if (myVector.empty()){
		return;
	}
	int localMin = myVector[0];
	int localMax = myVector[0];
	for (std::vector<int>::const_iterator iter = myVector.begin(); iter != myVector.end(); ++iter){
		if (*iter < localMin){
			localMin = *iter;
		}
		if (*iter > localMax){
			localMax = *iter;
		}
	}

	boost::mutex::scoped_lock lock(mutex_);
	if (localMin < min_){
		min_ = localMin;
	}
	if (localMax > max_){
		max_ = localMax;
	}
}

task4_5::solution::solution(const data_type& data) : min_ (0), max_ (0), dataSize_ (data.size()), ptrData_ (&data)
{
	int initialIndex = findFirstNonEmpty(data);
	if (initialIndex == -1){
		std::cout << "Vector is empty" << std::endl;
	}
	else {
		min_ = data[initialIndex][0];
		max_ = data[initialIndex][0];
		
		for (size_t j = 0; j < data.size(); ++j){
			threads_.create_thread(boost::bind(&task4_5::solution::findLocalMinAndMax, this, (*ptrData_)[j]));
		}
		threads_.join_all();
	}
}

int task4_5::solution::get_min() const {
	return min_;
}

int task4_5::solution::get_max() const {
	return max_;
}
