#ifndef _MULTICAST_COMMUNICATION_QUOTE_MESSAGE_H_
#define _MULTICAST_COMMUNICATION_QUOTE_MESSAGE_H_

#include <boost/shared_ptr.hpp>
#include <string>
#include <boost/cstdint.hpp>


namespace multicast_communication
{
	class quote_message
	{
		std::string qt_security_symbol_;
		double qt_bid_price_;
		double qt_bid_volume_;
		double qt_offer_price_;
		double qt_offer_volume_;
		boost::uint32_t qt_hours_;
		boost::uint32_t qt_minutes_;
		boost::uint32_t qt_time_;

		void init_short_qt_msg(const std::string & one_msg);
		void init_long_qt_msg(const std::string & one_msg);
		double get_price(const size_t start_pos_den, const size_t start_pos_price, const size_t price_len, const std::string & one_msg);
		void get_time(const std::string & one_msg);
		std::string delete_spaces(const std::string & str);

	public:
		explicit quote_message(const std::string & one_msg);
		explicit quote_message();
		~quote_message();
		const std::string security_symbol() const;
		const double bid_price() const;
		const double bid_volume() const;
		const double offer_price() const;
		const double offer_volume() const;
		const boost::uint32_t minutes() const;
		const boost::uint32_t hours() const;
		const boost::uint32_t time() const;
	};

	typedef boost::shared_ptr< quote_message > quote_message_ptr;
}

#endif // _MULTICAST_COMMUNICATION_QUOTE_MESSAGE_H_
