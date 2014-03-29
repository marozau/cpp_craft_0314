#include "b_message.h"

task4_4::b_message::b_message( std::istream& inp )
{
	inp >> length_;
	content_ = new char[ length_ ];
	inp.read( content_, length_ );
}

task4_4::message_ptr task4_4::b_message::create_message( std::istream& inp )
{
	return message_ptr( new b_message( inp ) );
}

task4_4::b_message::~b_message()
{
	delete [] content_;
}

const char task4_4::b_message::type() const
{
	return 'B';
}
const std::string task4_4::b_message::str() const
{
	return std::string();
}
