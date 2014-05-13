#ifndef _MULTICAST_COMMUNICATION_TRADE_MESSAGE_H_
#define _MULTICAST_COMMUNICATION_TRADE_MESSAGE_H_

#include <boost/shared_ptr.hpp>
#include <string>
#include <boost/cstdint.hpp>

namespace multicast_communication
{
	class trade_message
	{
		std::string tr_security_symbol_;
		double tr_price_;
		double tr_volume_;
		boost::uint32_t tr_hours_;
		boost::uint32_t tr_minutes_;
		boost::uint32_t tr_time_;

		void init_short_tr_msg(const std::string & one_msg);
		void init_long_tr_msg(const std::string & one_msg);
		void get_time(const std::string & one_msg);
		std::string delete_spaces(const std::string & str);

	public:
		explicit trade_message(const std::string & one_msg);
		explicit trade_message();
		~trade_message();

		const std::string security_symbol() const;
		const double price() const;
		const double volume() const;
		const boost::uint32_t hours() const;
		const boost::uint32_t minutes() const;
		const boost::uint32_t time() const;
	};
	typedef boost::shared_ptr< trade_message > trade_message_ptr;
}

#endif // _MULTICAST_COMMUNICATION_TRADE_MESSAGE_H_
