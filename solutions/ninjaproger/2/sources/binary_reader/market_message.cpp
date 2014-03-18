#include "market_message.h"
#include <cstring>


typedef union
{
    char chars[sizeof(uint32_t)];
    uint32_t integer;
}Uint32Union;


binary_reader::market_message::market_message( std::ifstream& in )
{
    Uint32Union rdUnion;
    in.read(rdUnion.chars, sizeof(uint32_t));
	_type = rdUnion.integer;
    in.read(rdUnion.chars, sizeof(uint32_t));
    _time = rdUnion.integer;
    in.read(rdUnion.chars, sizeof(uint32_t));
    _len = rdUnion.integer;
    
    _msg = new char[_len+1];
    in.read(_msg,_len);
    _msg[_len]=0;
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
    Uint32Union wrUnion;
    wrUnion.integer = _type;
    out.write(wrUnion.chars, sizeof(uint32_t));
	wrUnion.integer = _time;
    out.write(wrUnion.chars, sizeof(uint32_t));
    wrUnion.integer = _len;
    out.write(wrUnion.chars, sizeof(uint32_t));
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
const char* const binary_reader::market_message::msg() const
{
	return _msg;
}
