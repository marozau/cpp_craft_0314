#include "trade_message.h"
#include <boost\lexical_cast.hpp>

multicast_communication::trade_message::trade_message( trade_callback_type handler )
		: handler_( handler )
	{}

std::string multicast_communication::trade_message::security_symbol() const
{
	std::string temp;
	for( size_t i = 0; i < security_symbol_.length() && security_symbol_[ i ] != ' '; ++i )
		temp += security_symbol_[ i ];
	return temp;
}

double multicast_communication::trade_message::price() const
{
	return boost::lexical_cast< double >( trade_price_ );
}

double multicast_communication::trade_message::volume() const
{
	return boost::lexical_cast< double >( trade_volume_ );
}

boost::uint32_t multicast_communication::trade_message::minute() const
{
	return ( minute_[ 0 ] - '0' ) * 60 + ( minute_[1] - '0' ) ;

}

void multicast_communication::trade_message::get_string( std::string& Dest, std::stringstream& Source, size_t len )
{
	while( len )
	{
		if( !Source.good() )
			return;
		Dest += static_cast< char >( Source.get() );
		--len;
	}
}

void multicast_communication::trade_message::skip( std::stringstream& Source, size_t len )
{
	std::streamoff pos = Source.tellg();
	pos += len;
	Source.seekg( pos );
}

void multicast_communication::trade_message::parse( std::stringstream& in )
{
	const char category = static_cast< const char >( in.get() );
	const char type = static_cast< const char >( in.get() );
	skip( in, 16 );
	get_string( minute_, in, 6 );
	if( type == 'I' && ( ( category == 'E' || category == 'L' ) ) )
	{
		get_string( security_symbol_, in, 3 );
		skip( in, 1 );
		get_string( trade_volume_, in, 4 );
		get_string( price_denominator_indicator_, in, 1 );
		get_string( trade_price_, in, 8 );
		skip( in, 3 );
		handler_( shared_from_this() );
	}
	else if( type == 'B' && ( (  category == 'B' || category == 'E' || category == 'L' ) )  )
	{
		get_string( security_symbol_, in, 11 );
		skip( in, 21 );
		get_string( price_denominator_indicator_, in, 1 );
		get_string( trade_price_, in, 12 );
		get_string( trade_volume_, in, 9 );
		skip( in, 4 );
		handler_( shared_from_this() );
	}
	else
		throw std::exception( "T : Unkown type or category" );
}