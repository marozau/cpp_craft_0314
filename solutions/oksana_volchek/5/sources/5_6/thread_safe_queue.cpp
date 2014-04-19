#include "thread_safe_queue.h"

namespace task5_6
{
	void instantiation_test();
}

void task5_6::instantiation_test()
{
	thread_safe_queue< int > tsqi;
	tsqi.push( 45 );
	int res;
	tsqi.pop( res );
	tsqi.empty();
	tsqi.size();
}
