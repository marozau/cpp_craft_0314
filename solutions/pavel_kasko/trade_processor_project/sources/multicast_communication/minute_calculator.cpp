#include "minute_calculator.h"
#include <vector>

namespace multicast_communication
{
	void minute_calculator::SaveOne(std::string& input, message_type type)
	{
		int time_dec_dif = 48;

		if(type == message_type::QUOTE)
		{
			auto v = _cnv.ConvertToQuote(input);

			for(auto i = (*v).begin(); i != (*v).end(); ++i)
			{
				std::string tstp = (**i).timestamp();
				int h = ((int)tstp[0]) - time_dec_dif;
				int m = ((int)tstp[1]) - time_dec_dif;
				int s = ((int)tstp[2]) - time_dec_dif;
			}

			delete v;
		}
		else
		{
			auto v = _cnv.ConvertToTrade(input);

			for(auto i = (*v).begin(); i != (*v).end(); ++i)
			{
				std::string tstp = (**i).timestamp();
				int h = ((int)tstp[0]) - time_dec_dif;
				int m = ((int)tstp[1]) - time_dec_dif;
				int s = ((int)tstp[2]) - time_dec_dif;
			}

			delete v;
		}
	}
}
