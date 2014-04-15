#include "a_message.h"

#include <stdexcept>

task4_4::a_message::a_message( std::istream& inp )
{

	char content[ content_size ];

	inp.read( content, content_size );
	const size_t read_bytes = inp.gcount();

	if( !inp )
	{
		throw std::logic_error( "bad input stream, a_message cannot be read" );
	}

	content_ = std::string( content, read_bytes );
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
	return "a_message(" + content_ + ")";
}
