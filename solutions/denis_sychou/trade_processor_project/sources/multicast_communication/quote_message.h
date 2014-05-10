#ifndef _MULTICAST_COMMUNICATION_QUOTE_MESSAGE_H_
#define _MULTICAST_COMMUNICATION_QUOTE_MESSAGE_H_

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/cstdint.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <string>
#include <sstream>

namespace multicast_communication
{
	class quote_message;

	typedef boost::shared_ptr< quote_message > quote_message_ptr;
	typedef boost::function< void( const quote_message_ptr& ) > quote_callback_type;

	class quote_message : virtual public boost::enable_shared_from_this< quote_message >
	{
		quote_callback_type handler_;

		std::string security_symbol_
					, bid_price_
					, bid_price_denominator_indicator_
					, bid_size_of_units_of_trade_
					, offer_price_
					, offer_price_denominator_indicator_
					, offer_size_of_units_of_trade_
					, lower_limit_price_band_denominator_indicator_
					, lower_limit_price_band_
					, bid_size_in_units_of_trade_
					, upper_limit_price_band_denominator_indicator_
					, upper_limit_price_band_ 
					, offer_size_in_units_of_trade_
					, minute_;

		void get_string( std::string& Dest, std::stringstream& Source, size_t len );
		void skip( std::stringstream& Source, size_t len );
	public:
		explicit quote_message( quote_callback_type handler );
		explicit quote_message() : security_symbol_( "" )
								   , bid_price_( "0" )
								   , bid_price_denominator_indicator_( "" )
								   , bid_size_of_units_of_trade_( "" )
								   , offer_price_( "0" )
								   , offer_price_denominator_indicator_( "" )
								   , offer_size_of_units_of_trade_( "0" )
								   , lower_limit_price_band_denominator_indicator_( "" )
								   , lower_limit_price_band_( "" )
								   , bid_size_in_units_of_trade_( "0" )
								   , upper_limit_price_band_denominator_indicator_( "" )
								   , upper_limit_price_band_ ( "" )
								   , offer_size_in_units_of_trade_( "" )
								   , minute_( "" )

		{ }
		virtual ~quote_message() {}

		std::string security_symbol() const;
		double bid_price() const;
		double bid_volume() const;
		double offer_price() const;
		double offer_volume() const;
		boost::uint32_t minute() const;

		void parse( std::stringstream& in );
	};
}

#endif // _MULTICAST_COMMUNICATION_QUOTE_MESSAGE_H_
