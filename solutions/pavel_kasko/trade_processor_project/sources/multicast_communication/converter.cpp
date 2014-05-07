#include "converter.h"
#include <boost\lexical_cast.hpp>

namespace multicast_communication
{
	void converter::ConvertToQuote(std::string input)
	{
		size_t pos = 0;

		if (input[pos++] != SOH)
			return;

		while (pos < input.length() || input[pos] != ETX)
		{
			char message_category = input[pos++];
			char message_type = input[pos++];

			pos += 16; // timestamp position (need 5 more);
			
			pos += 6; //message first position

			if (message_category != 'E')
				return;
			if (message_type == 'B')
			{
				//long
			}
			else
			{
				//D = short
			}
			//Message Network 1 Retransmission Requester 2 Header Identifier 1 Reserved 2 Message Sequence Number 9 Participant ID 1 Time Stamp 6 Total Length : 24
		}
	}



	void converter::ConvertToTrade(std::string input)
	{
	}
}