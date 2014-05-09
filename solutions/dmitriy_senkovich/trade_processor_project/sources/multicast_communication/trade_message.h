#ifndef _MULTICAST_COMMUNICATION_TRADE_MESSAGE_H_
#define _MULTICAST_COMMUNICATION_TRADE_MESSAGE_H_

#include <boost/shared_ptr.hpp>
#include <string>
#include <boost/cstdint.hpp>

namespace trade_processor_project
{
	class trade_message
	{
		std::string security_symbol_;
		
		double trade_volume_;
		std::string price_denominator_indicator_;
		double trade_price_;

		boost::uint32_t minute_;

	public:
		explicit trade_message();
		std::string security_symbol() const;
		double price() const;
		double volume() const;
		std::string price_denominator_indicator() const;
		boost::uint32_t minute() const;
		std::string& set_security_symbol();
		double& set_trade_volume();
		std::string& set_price_denominator_indicator();
		double& set_trade_price();
		boost::uint32_t& set_minute();
	};
	typedef boost::shared_ptr< trade_message > trade_message_ptr;
}

#endif // _MULTICAST_COMMUNICATION_TRADE_MESSAGE_H_
