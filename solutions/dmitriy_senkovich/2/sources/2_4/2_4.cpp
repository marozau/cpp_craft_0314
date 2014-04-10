#include "trade_filter.h"
#include <iostream>

int main(){

	try{

		trade_filter::trade_filter solution;
		solution.run();

	}

	catch(std::exception& e){

		std::cerr << e.what();
		return 1;

	}

	return 0;

}