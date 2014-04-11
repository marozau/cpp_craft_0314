#include "small_buffer.h"
#include <iostream>

int main(){

	try{

		small_buffer::small_buffer solution;
		solution.run();

	}

	catch(std::exception& e){

		std::cerr << e.what();
		return 1;

	}

	return 0;

}