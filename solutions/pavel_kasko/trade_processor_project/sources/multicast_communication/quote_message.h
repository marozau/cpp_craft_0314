#ifndef _MULTICAST_COMMUNICATION_QUOTE_MESSAGE_H_
#define _MULTICAST_COMMUNICATION_QUOTE_MESSAGE_H_

#include <boost/shared_ptr.hpp>
#include "message_types.h"

namespace multicast_communication
{
	class quote_message
	{
		std::string _timestamp;
		const std::string _security_symbol;
		double _bid_price;
		double _bid_volume;
		double _offer_price;
		double _offer_volume;

	public:
		explicit quote_message(std::string _timestamp, std::string _security_symbol, double _bid_price, double _bid_volume, 
			double _offer_price, double _offer_volume);
		explicit quote_message();

		std::string timestamp() const;
		std::string security_symbol() const;
		double bid_price() const;
		double bid_volume() const;
		double offer_price() const;
		double offer_volume() const;
	};

	typedef boost::shared_ptr< quote_message > quote_message_ptr;
}

#endif // _MULTICAST_COMMUNICATION_QUOTE_MESSAGE_H_
