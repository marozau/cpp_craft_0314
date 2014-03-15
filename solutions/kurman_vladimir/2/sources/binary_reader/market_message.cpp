#include "market_message.h"
#include <cstring>

namespace market_message_impl
{
	template <class T>
	void read(std::ifstream & in, T & t)
	{
		in.read(reinterpret_cast<char*>(&t), sizeof(t));
	}
	template <class T>
	void read(std::ifstream & in, T * t, size_t n)
	{
		in.read(reinterpret_cast<char*>(t), sizeof(t)* n);
	}
}

binary_reader::market_message::market_message( std::ifstream& in )
{
	using namespace market_message_impl;
	read(in, type_);
	read(in, time_);
	read(in, len_);
	if (len_ > 0 && len_ < 100)
	{
		char * msg = new char[len_];
		read(in, msg, len_);
	}
}

binary_reader::market_message::market_message( const boost::uint32_t type, const boost::uint32_t time, const char* const msg )
{
	// your code
}

void binary_reader::market_message::write( std::ofstream& out )
{
	// your code
}

binary_reader::market_message::~market_message()
{
	// your code
}

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

size_t binary_reader::market_message::size()
{
	return sizeof(type_)+sizeof(time_)+sizeof(len_)+len_;
}
