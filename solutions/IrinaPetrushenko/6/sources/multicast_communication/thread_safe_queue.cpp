#include "thread_safe_queue.h"

namespace multicast_communication
{
	void instantiation_test();
}

void multicast_communication::instantiation_test()
{
	thread_safe_queue< int > tsqi;
	tsqi.push( 45 );
	int res;
	tsqi.pop( res );
	tsqi.empty();
	tsqi.size();
}
