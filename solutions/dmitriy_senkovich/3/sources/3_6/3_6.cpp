#include "th_binary_datafeed.h"

int main()
{
	try
	{
		th_binary_datafeed::th_binary_datafeed solution;
		solution.read_set_threads_and_run_process();
	}
	catch( std::exception& e )
	{
		std::cerr << e.what() << "\n";
		return 1;
	}
	return 0;
}