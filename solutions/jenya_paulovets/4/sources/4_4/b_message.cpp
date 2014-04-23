#include "b_message.h"

#include <stdexcept>
#include <iostream>
#include <boost/lexical_cast.hpp>

task4_4::b_message::b_message( std::istream& inp ):length_(0)
{
	inp >> length_;

	if ( !inp )
			throw std::logic_error("bad input stream, b_message cannot be readed");

	content_ = new char[ length_ + 1];
	content_[length_] = '\0';

	inp.get();

	inp.read( content_, length_ );

	if ( inp.eof() )
	{
		delete []content_;
		throw std::logic_error("bad input stream, b_message cannot be readed");
	}
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
	return std::string( "b_message(").append(boost::lexical_cast<std::string>(length_)).append("|").append(content_).append(")");
}
