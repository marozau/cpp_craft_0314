#include "market_message.h"
#include <cstring>

binary_reader::market_message::market_message( std::ifstream& input )
	: msg_( NULL )
{
	input.read( reinterpret_cast< char* >( &type_ ), sizeof( type_ ) );
	input.read( reinterpret_cast< char* >( &time_ ), sizeof( time_ ) );
	input.read( reinterpret_cast< char* >( &len_ ), sizeof( len_ ) );
	msg_ = new char[ len_ ];
	input.read( msg_, len_ );
}

binary_reader::market_message::market_message( const boost::uint32_t type, const boost::uint32_t time, const char* const msg )
: type_ ( type )
, time_( time )
{
	len_ = static_cast< boost::uint32_t >( strlen( msg ) );
	msg_ = new char[ len_ ];
	memcpy( msg_, msg, len_ );
}
void binary_reader::market_message::write( std::ofstream& output )
{
	output.write( reinterpret_cast< char* >( &type_ ), sizeof( type_ ) );
	output.write( reinterpret_cast< char* >( &time_ ), sizeof( time_ ) );
	output.write( reinterpret_cast< char* >( &len_ ), sizeof( len_ ) );
	output.write( msg_, len_ );
}

binary_reader::market_message::~market_message()
{
	delete [] msg_;
}
//
boost::uint32_t binary_reader::market_message::type() const
{
	return type_;
}
boost::uint32_t binary_reader::market_message::time() const
{
	return time_;
}
const char* const binary_reader::market_message::msg() const
{
	return msg_;
}

boost::uint32_t binary_reader::market_message::len() const
{
	return len_;
}