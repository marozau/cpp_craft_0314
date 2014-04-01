#include "market_message.h"
#include <cstring>


binary_reader::market_message::market_message( std::ifstream& in )
{

    in.read( reinterpret_cast< char * >( &_type), sizeof(_type));
    in.read( reinterpret_cast< char * >( &_time), sizeof(_time));
    in.read( reinterpret_cast< char * >( &_len), sizeof(_len));

    _msg = new char[_len];
    if(_len)
        in.read(_msg,_len);
}

binary_reader::market_message::market_message( const boost::uint32_t type, const boost::uint32_t time,const boost::uint32_t len,const char* const msg )
{
	_type = type;
    _time = time;
    _len = len;
    _msg = new char[_len];
    memcpy(_msg, msg, _len);
}
void binary_reader::market_message::write( std::ofstream& out )
{
    
    out.write( reinterpret_cast< const char * >( &_type), sizeof(_type));
    out.write( reinterpret_cast< const char * >( &_time), sizeof(_time));
    out.write( reinterpret_cast< const char * >( &_len), sizeof(_len));
    
    out.write(_msg,_len);
}

binary_reader::market_message::~market_message()
{
	delete [] _msg;
}

boost::uint32_t binary_reader::market_message::type() const
{
	return _type;
}
boost::uint32_t binary_reader::market_message::time() const
{
	return _time;
}
boost::uint32_t binary_reader::market_message::msg_len() const
{
	return _len;
}
const char* const binary_reader::market_message::msg() const
{
	return _msg;
}
