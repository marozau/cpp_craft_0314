#include "b_message.h"
#include <boost/format.hpp>
task4_4::b_message::b_message( std::istream& inp )
{
    inp >> length_;
    if(inp.eof())
        throw std::logic_error("b message cannot be readed!!!");
    char spaceChar;
    content_ = new char[ length_ + 1];
    inp.get( spaceChar );
    inp.read( content_, length_ );
    content_[length_] = '\0';
    if( inp.gcount( ) != length_){
        delete [ ] content_;
        throw std::logic_error("b message is fail");
    }
    if( inp.eof( ) ){
        delete [ ] content_;
        throw std::logic_error("b_message cannot be readed!!!");
    }

}

task4_4::message_ptr task4_4::b_message::create_message( std::istream& inp )
{
	return message_ptr( new b_message( inp ) );
}

task4_4::b_message::~b_message()
{
    if(content_)
        delete [] content_;
}

const char task4_4::b_message::type() const
{
	return 'B';
}
const std::string task4_4::b_message::str() const
{

    return std::string() = boost::str(boost::format("b_message(%1%|%2%)") % length_ % content_);
}
