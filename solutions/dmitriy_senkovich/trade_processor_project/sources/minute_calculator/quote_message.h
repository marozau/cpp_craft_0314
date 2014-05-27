#ifndef _MULTICAST_COMMUNICATION_QUOTE_MESSAGE_H_
#define _MULTICAST_COMMUNICATION_QUOTE_MESSAGE_H_

#include <boost/shared_ptr.hpp>
#include <string>
#include <boost/cstdint.hpp>

namespace trade_processor_project
{
	class quote_message
	{
		std::string security_symbol_;

		double bid_price_;
		std::string bid_price_denominator_indicator_;
		double bid_size_of_units_of_trade_;
		double offer_price_;
		std::string offer_price_denominator_indicator_;
		double offer_size_of_units_of_trade_;

		std::string lower_limit_price_band_denominator_indicator_;
		double lower_limit_price_band_;
		double bid_size_in_units_of_trade_;
		std::string upper_limit_price_band_denominator_indicator_;
		double upper_limit_price_band_;
		double offer_size_in_units_of_trade_;

		boost::uint32_t minute_;

	public:
		bool if_long;
		explicit quote_message();
		std::string security_symbol() const;
		double bid_price() const;
		double bid_volume() const;
		double offer_price() const;
		double offer_volume() const;
		boost::uint32_t minute() const;
		std::string bid_price_denominator_indicator() const;
		std::string offer_price_denominator_indicator() const;
		std::string lower_limit_price_band_denominator_indicator() const;
		std::string upper_limit_price_band_denominator_indicator() const;
		std::string& set_security_symbol();
		double& set_bid_price();
		std::string& set_bid_price_denominator_indicator();
		double& set_bid_size_of_units_of_trade();
		double& set_offer_price();
		std::string& set_offer_price_denominator_indicator();
		double& set_offer_size_of_units_of_trade();
		std::string& set_lower_limit_price_band_denominator_indicator();
		double& set_lower_limit_price_band();
		double& set_bid_size_in_units_of_trade();
		std::string& set_upper_limit_price_band_denominator_indicator();
		double& set_upper_limit_price_band();
		double& set_offer_size_in_units_of_trade();
		boost::uint32_t& set_minute();
	};
	typedef boost::shared_ptr< quote_message > quote_message_ptr;
}

#endif // _MULTICAST_COMMUNICATION_QUOTE_MESSAGE_H_
