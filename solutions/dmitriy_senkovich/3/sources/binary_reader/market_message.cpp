#include "market_message.h"

binary_reader::market_message::market_message( std::ifstream& in )
{
	if ( !in.read( reinterpret_cast<char*> ( &type_ ), sizeof( boost::uint32_t ) ) )
		throw std::exception( "Error while reading data type in input file " );
	if ( !in.read( reinterpret_cast<char*> ( &time_ ), sizeof( boost::uint32_t ) ) )
		throw std::exception( "Error while reading data time in input file " );
	if ( !in.read( reinterpret_cast<char*> ( &len_ ), sizeof( boost::uint32_t ) ) )
		throw std::exception( "Error while reading data len in input file" );
	msg_ = new char[len_+1];
	if ( !in.read( msg_, sizeof( char )*len_ ) )
		throw std::exception( "Error while reading data msg in input file " );
	msg_[len_] = '\0';
}
binary_reader::market_message::market_message( const boost::uint32_t type, const boost::uint32_t time, const boost::uint32_t len, const char* const msg )
{
	type_ = type;
	time_ = time;
	len_ = len;
	memcpy( msg_, msg, len_ );
}
void binary_reader::market_message::write( std::ofstream& out )
{
	if ( !out.write( reinterpret_cast<char*> (&type_), sizeof( boost::uint32_t ) ) )
		throw std::exception( "Error while writing data type in output file " );
	if ( !out.write( reinterpret_cast<char*> (&time_), sizeof( boost::uint32_t ) ) )
		throw std::exception( "Error while writing data time in output file " );
	if ( !out.write( reinterpret_cast<char*> (&len_), sizeof( boost::uint32_t ) ) )
		throw std::exception( "Error while writing data len in output file " );
	if ( !out.write( msg_, sizeof( char )*len_ ) )
		throw std::exception( "Error while writing data msg in output file " );
}

binary_reader::market_message::~market_message()
{
	delete msg_;
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
boost::uint32_t binary_reader::market_message::len() const
{
	return len_;
}
const char* const binary_reader::market_message::msg() const
{
	return msg_;
}
