#include "a_message.h"

#include <stdexcept>
#include <sstream>

task4_4::a_message::a_message( std::istream& inp )
{
	inp.read( content_, content_size );
	if ( inp.eof() )
		throw std::logic_error("bad input stream, a_message cannot be readed");
}

task4_4::message_ptr task4_4::a_message::create_message( std::istream& inp )
{
	return message_ptr( new a_message( inp ) );
}

task4_4::a_message::~a_message()
{
}
//
const char task4_4::a_message::type() const
{
	return 'A';
}
const std::string task4_4::a_message::str() const
{
    std::stringstream message;
    char str[ content_size + 1];

    memmove(str, content_, content_size);
    str[content_size] = '\0';

    message << "a_message(" << str << ")";
	return message.str();
}
