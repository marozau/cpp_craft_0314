#ifndef _MULTICAST_COMMUNICATION_QUOTE_MESSAGE_H_
#define _MULTICAST_COMMUNICATION_QUOTE_MESSAGE_H_

#include <boost/shared_ptr.hpp>

namespace multicast_communication
{
	class quote_message
	{
	public:
		std::string security_symbol() const;
		double bid_price() const;
		double bid_volume() const;
		double offer_price() const;
		double offer_volume() const;
	};

	typedef boost::shared_ptr< quote_message > quote_message_ptr;
}

#endif // _MULTICAST_COMMUNICATION_QUOTE_MESSAGE_H_
