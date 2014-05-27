#ifndef _MULTICAST_COMMUNICATION_TRADE_MESSAGE_H_
#define _MULTICAST_COMMUNICATION_TRADE_MESSAGE_H_

#include <boost/shared_ptr.hpp>

namespace multicast_communication
{
	class trade_message
	{
		std::string _timestamp;
		std::string _security_symbol;
		double _price;
		double _volume;

	public:
		trade_message();
		trade_message(std::string _timestamp, std::string _security_symbol, double _price, double _volume);
		
		std::string timestamp() const;
		std::string security_symbol() const;
		double price() const;
		double volume() const;
	};

	typedef boost::shared_ptr< trade_message > trade_message_ptr;
}

#endif // _MULTICAST_COMMUNICATION_TRADE_MESSAGE_H_
