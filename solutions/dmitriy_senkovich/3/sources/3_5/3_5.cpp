#include "th_small_buffer.h"
#include <iostream>

int main()
{
	try
	{

		th_small_buffer::th_small_buffer solution;
		solution.set_threads_and_run();

	}
	catch(std::exception& e)
	{

		std::cerr << e.what();
		return 1;

	}

	return 0;
}