#include "b_message.h"
#include <sstream>


task4_4::b_message::b_message( std::istream& inp )
    : length_(0)
    , content_(nullptr)
{
    try
    {
        if ( inp.eof() )
        {
            throw std::logic_error("bad input stream, a_message cannot be readed");
        }

        inp >> length_;
        if ( inp.eof() )
        {
            throw std::logic_error("invalid file length");
        }

        char space = 0;
        inp.read(&space, sizeof(space));

        content_ = new char[ length_ + 1];
        inp.read( content_, length_);
        content_[length_] = '\0';

        if ( inp.eof() )
        {
            throw std::logic_error("bad input stream, a_message cannot be readed");
        }
    }
    catch(...)
    {
        clear();
        throw;
    }
}

task4_4::message_ptr task4_4::b_message::create_message( std::istream& inp )
{
	return message_ptr( new b_message( inp ) );
}

task4_4::b_message::~b_message()
{
    clear();
}

const char task4_4::b_message::type() const
{
	return 'B';
}

const std::string task4_4::b_message::str() const
{
    std::stringstream str;
    str << "b_message("
        << length_
        << "|"
        << content_
        << ")";
    
    return str.str();
}


void task4_4::b_message::clear()
{
    if (content_)
    {
        delete [] content_;
        content_ = nullptr;
    }
}

