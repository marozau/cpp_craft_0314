#include "market_message.h"
#include <cstring>
#include <iostream>

binary_reader::market_message::market_message( std::ifstream& in )
{
	if(!in.read(reinterpret_cast<char*>(&type_), sizeof(boost:: uint32_t)) )
	{
		std::cerr<<"Input is incorrect"<< std::endl;
		return;
	}
	if(!in.read(reinterpret_cast<char*>(&time_), sizeof(boost:: uint32_t)) )
	{
		std::cerr<<"Input is incorrect"<< std::endl;
		return;
	}
	if(!in.read(reinterpret_cast<char*>(&len_), sizeof(boost:: uint32_t)) )
	{
		std::cerr<<"Input is incorrect"<< std::endl;
		return;
	}
	msg_ = new char[len_];
	if(!in.read(msg_, len_) )
	{
		std::cerr<<"Input is incorrect"<< std::endl;
		return;
	}
}
binary_reader::market_message::market_message( const boost::uint32_t type, const boost::uint32_t time, const char* const msg )
{
	type_=type;
	time_=time;
	len_ = static_cast<boost::uint32_t>(strlen(msg));
	memcpy(msg_,msg, 8);
}
void binary_reader::market_message::write( std::ofstream& out )
{
	if(!out.write(reinterpret_cast<char*>(&type_),sizeof(type_)) )
	{
		std::cerr<<"Can't write"<< std::endl;
		return;
	}
	if(!out.write(reinterpret_cast<char*>(&time_), sizeof(time_)) )
	{
		std::cerr<<"Can't write"<< std::endl;
		return;
	}
	if(!out.write(reinterpret_cast<char*>(&len_), sizeof(len_)) )
	{
		std::cerr<<"Can't write"<< std::endl;
		return;
	}
	if(!out.write(msg_, sizeof(msg_)) )
	{
		std::cerr<<"Can't write"<< std::endl;
		return;
	}

}

binary_reader::market_message::~market_message()
{
	delete [] msg_;
}
//
boost::uint32_t binary_reader::market_message::type() const
{
	return type_;
}
boost::uint32_t binary_reader::market_message::time() const
{
	return time_;
}
const char* const binary_reader::market_message::msg() const
{
	return msg_;
}

boost::uint32_t binary_reader::market_message::len() const
{
	return len_;
}
