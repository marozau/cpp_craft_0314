#include "market_message.h"
#include <cstring>

binary_reader::market_message::market_message( std::ifstream& in )
{
	// your code
}
binary_reader::market_message::market_message( const boost::uint32_t type, const boost::uint32_t time, const char* const msg )
{
	// your code
}
void binary_reader::market_message::write( std::ofstream& out )
{
	// your code
}

binary_reader::market_message::~market_message()
{
	// your code
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
