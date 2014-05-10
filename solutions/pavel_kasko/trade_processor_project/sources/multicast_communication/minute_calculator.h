#ifndef MINUTE_CALCULATOR
#define MINUTE_CALCULATOR

#include<string>
#include "message_types.h"
#include "converter.h"

namespace multicast_communication
{
	class minute_calculator
	{
		converter _cnv;
	public:
		void SaveOne(std::string&, message_type type);
	};
}

#endif //MINUTE_CALCULATOR