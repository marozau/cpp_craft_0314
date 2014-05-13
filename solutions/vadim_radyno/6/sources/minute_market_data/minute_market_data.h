#ifndef _MINUTE_MARKET_DATA_H_
#define _MINUTE_MARKET_DATA_H_

#include <boost/thread.hpp>

namespace minute_market_data
{
	static boost::condition_variable cond_var_press_ctrl_c; 
	class solution
	{
	public:
		void start();
	};
}

#endif // _MINUTE_MARKET_DATA_H_