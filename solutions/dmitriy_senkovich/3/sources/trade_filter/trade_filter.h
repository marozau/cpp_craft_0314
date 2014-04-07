#ifndef _trade_filter_
#define _trade_filter_

#include "market_message.h"

#include <boost/thread.hpp>

namespace trade_filter{

	class trade_filter{

	public:

		void run( const std::string& input, const std::string& output );

	};

}

#endif