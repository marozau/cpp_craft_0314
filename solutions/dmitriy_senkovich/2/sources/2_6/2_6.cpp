#include "binary_datafeed.h"
#include <iostream>

int main(){

	try{

		binary_datafeed::binary_datafeed solution;
		solution.run();

	}
	catch( std::exception& e ){

		std::cerr << e.what();
		return 1;

	}

	return 0;

}