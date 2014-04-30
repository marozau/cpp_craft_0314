#include "b_message.h"
#include <stdexcept>
#include <sstream>

task4_4::b_message::b_message(std::istream& inp) : content_(nullptr)
{
	inp >> length_;
	if (inp.eof())
		throw std::logic_error("bad input stream");
	
	std::string tempStr;
	inp >> tempStr;
	if (tempStr.length() != length_)
		throw std::logic_error("bad input stream");
	
	content_ = new char[length_];
	std::move(tempStr.begin(), tempStr.end(), content_);
}

task4_4::message_ptr task4_4::b_message::create_message( std::istream& inp )
{
	return message_ptr( new b_message( inp ) );
}

task4_4::b_message::~b_message()
{
	if (content_)
		delete [] content_;
}

const char task4_4::b_message::type() const
{
	return 'B';
}
const std::string task4_4::b_message::str() const
{
	std::stringstream strStream;

	strStream << "b_message(" << length_ << "|";
	strStream.write(content_, length_);
	strStream << ")";
	
	std::string result;
	strStream >> result;
	return result;
}
