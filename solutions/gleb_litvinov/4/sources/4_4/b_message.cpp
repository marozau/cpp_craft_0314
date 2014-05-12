#include "b_message.h"
#include <boost/lexical_cast.hpp>

task4_4::b_message::b_message( std::istream& inp )
{
	inp >> length_;
	if(inp.eof())
		throw(std::logic_error("bad input stream, b_message cannot be readed"));
	inp.get();
	content_ = new char[ length_ +1];
	if(!inp.read( content_, length_ ))
	{
		delete[] content_;
		throw(std::logic_error("bad input stream, a_message cannot be readed"));
	}
	content_[length_]='\0';
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
	return "b_message("+boost::lexical_cast<std::string>(length_)+"|"+std::string(content_)+")";
}
