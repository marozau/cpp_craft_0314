#include "b_message.h"

#include <stdexcept>
#include <boost/lexical_cast.hpp>


task4_4::b_message::b_message( std::istream& inp ) : length_ (0), content_ (NULL)
{
	inp >> length_ ;
	if (inp.eof()){
		throw std::logic_error ("bad input stream, a_message cannot be readed");
	}
	char separator;
	inp.get(separator);
	content_ = new char[length_ + 1];
	std::string tmp;
	inp >> tmp;
	if (tmp.length() != length_){
		delete [] content_;
		throw std::logic_error("incorrect length");
	}
	std::copy(tmp.begin(), tmp.end(), content_);
	content_[length_] = '\0';
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
	const std::string myString = "b_message(" + boost::lexical_cast<std::string>(length_) + "|" + boost::lexical_cast<std::string>(content_) + ")";
	return myString;
}
