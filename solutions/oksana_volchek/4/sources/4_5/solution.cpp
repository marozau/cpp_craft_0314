#include "solution.h"
#include <vector>

task4_5::solution::solution(const data_type& data) : min_ (0), max_ (0), dataSize_ (data.size()) {
	if (dataSize_ != 0){
		min_ = data[0][0];
		max_ = data[0][0];
		ptrData_ = &data;
		
		for (size_t j = 0; j < data.size(); ++j){
			threads_.create_thread(boost::bind(&task4_5::solution::findLocalMinAndMax, this, (*ptrData_)[j]));
		}
		threads_.join_all();
	}
	else {
		std::cout << "Vector is empty" << std::endl;
	}
}

void task4_5::solution::findLocalMinAndMax(const std::vector<int> & myVector){
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

int task4_5::solution::get_min() const {
	return min_;
}

int task4_5::solution::get_max() const {
	return max_;
}
