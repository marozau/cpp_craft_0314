#ifndef _MULTICAST_COMMUNICATION_TRADE_MESSAGE_H_
#define _MULTICAST_COMMUNICATION_TRADE_MESSAGE_H_

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/cstdint.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <string>
#include <sstream>

namespace multicast_communication
{
	class trade_message;

	typedef boost::shared_ptr< trade_message > trade_message_ptr;
	typedef boost::function< void( const trade_message_ptr& ) > trade_callback_type;

	class trade_message : public boost::enable_shared_from_this< trade_message >
	{
		trade_callback_type handler_;

		std::string security_symbol_
					, trade_volume_
					, price_denominator_indicator_
					, trade_price_
					, minute_;

		void get_string( std::string& Dest, std::stringstream& Source, size_t len );
		void skip( std::stringstream& Source, size_t len );
	public:
		explicit trade_message( trade_callback_type handler );
		explicit trade_message() : security_symbol_( "" )
								, trade_volume_( "" )
								, price_denominator_indicator_( "" )
								, trade_price_( "" )
								, minute_( "" )
		{}
		virtual ~trade_message() {}

		std::string security_symbol() const;
		double price() const;
		double volume() const;
		boost::uint32_t minute() const;

		void parse( std::stringstream& in );
	};
}

#endif // _MULTICAST_COMMUNICATION_TRADE_MESSAGE_H_
