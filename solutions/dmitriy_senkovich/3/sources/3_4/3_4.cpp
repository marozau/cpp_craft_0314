#include "th_trade_filter.h"

int main()
{
	try
	{
		th_trade_filter::th_trade_filter solution;
		solution.set_threads_and_run();
	}
	catch(std::exception& e)
	{
		std::cerr << e.what();
		return 1;
	}
	return 0;
}