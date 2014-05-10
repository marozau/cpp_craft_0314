#include "quote_message.h"
#include <boost\lexical_cast.hpp>


multicast_communication::quote_message::quote_message( quote_callback_type handler )
		: handler_( handler )
	{}

std::string multicast_communication::quote_message::security_symbol() const
{
	std::string temp;
	for( size_t i = 0; i < security_symbol_.length() && security_symbol_[ i ] != ' '; ++i )
		temp += security_symbol_[ i ];
	return temp;
}

double multicast_communication::quote_message::bid_price() const
{
	return boost::lexical_cast< double >( bid_price_ );
}

double multicast_communication::quote_message::bid_volume() const
{
	return boost::lexical_cast< double >( bid_size_in_units_of_trade_ );
}

double multicast_communication::quote_message::offer_price() const
{
	return boost::lexical_cast< double >( offer_price_ );
}

double multicast_communication::quote_message::offer_volume() const
{
	return boost::lexical_cast< double >( offer_size_in_units_of_trade_ );
}

boost::uint32_t multicast_communication::quote_message::minute() const
{
	return ( minute_[ 0 ] - '0' ) * 60 + ( minute_[1] - '0' ) ;

}

void multicast_communication::quote_message::get_string( std::string& Dest, std::stringstream& Source, size_t len )
{
	while( len )
	{
		if( !Source.good() )
			return;
		Dest += static_cast< char >( Source.get() );
		--len;
	}
}

void multicast_communication::quote_message::skip( std::stringstream& Source, size_t len )
{
	std::streamoff pos = Source.tellg();
	pos += len;
	Source.seekg( pos );
}

void multicast_communication::quote_message::parse( std::stringstream& in )
{
	const char category = static_cast< const char >( in.get() );
	const char type = static_cast< const char >( in.get() );
	skip( in, 16 );
	get_string( minute_, in, 6 );
	if( type == 'D' && ( ( category == 'E' || category == 'L' ) ) )
	{
		get_string( security_symbol_, in, 3 );
		skip( in, 3 );
		get_string( bid_price_denominator_indicator_, in, 1 );
		get_string( bid_price_, in, 8 );
		get_string( bid_size_in_units_of_trade_, in, 3 );
		skip( in, 1 );
		get_string( offer_price_denominator_indicator_, in, 1 );
		get_string( offer_price_, in, 8 );
		get_string( offer_size_in_units_of_trade_, in, 3 );
		skip( in, 3 );
		handler_( shared_from_this() );
	}
	else if( type == 'B' && ( (  category == 'B' || category == 'E' || category == 'L' ) ) )
	{
		get_string( security_symbol_, in, 11 );
		skip( in, 16 );
		get_string( lower_limit_price_band_denominator_indicator_, in, 1 );
		get_string( bid_price_, in, 12 );
		get_string( bid_size_in_units_of_trade_, in, 7 );
		get_string( upper_limit_price_band_denominator_indicator_, in, 1 );
		get_string( offer_price_, in, 12 );
		get_string( offer_size_in_units_of_trade_, in, 7 );
		skip( in, 11 );
		handler_( shared_from_this() );
	}
	else
		throw std::exception( "Q : Unkown type or category" );
}
