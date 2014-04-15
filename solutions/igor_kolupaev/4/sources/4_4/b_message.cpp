#include "b_message.h"

#include <sstream>

task4_4::b_message::b_message( std::istream& inp )
{
	inp >> length_;

	if( inp.eof() )
	{
		throw std::logic_error( "bad input stream, b_message cannot be readed" );
	}

	content_ = new char[ length_ + 1 ];

	inp.read( content_, 1 ); //skip space
	inp.read( content_, length_ );

	if( inp.eof() )
	{
		delete[ ] content_;		
		throw std::logic_error( "bad input stream, b_message cannot be readed" );
	}

	content_[ length_ ] = '\0';
}

task4_4::message_ptr task4_4::b_message::create_message( std::istream& inp )
{
	return message_ptr( new b_message( inp ) );
}

task4_4::b_message::~b_message()
{
	delete[] content_;
}

const char task4_4::b_message::type() const
{
	return 'B';
}
const std::string task4_4::b_message::str() const
{
	std::ostringstream iss;

	iss << "b_message(" << length_ << "|" << content_ << ")";

	return iss.str();
}
