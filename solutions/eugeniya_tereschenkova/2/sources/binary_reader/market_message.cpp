#include "market_message.h"
#include <cstring>
#include <iostream>
using namespace std;

binary_reader::market_message::market_message( std::ifstream& in )
{	
	if(!in.read(reinterpret_cast<char*>(&type_), sizeof(boost:: uint32_t)) )
		return;
	if(!in.read(reinterpret_cast<char*>(&time_), sizeof(boost:: uint32_t)) )
		return;
	if(!in.read(reinterpret_cast<char*>(&len_), sizeof(boost:: uint32_t)) )
		return;
	msg_ = NULL;
	msg_ = new char[len_+1];	
	if(!msg_)
		throw logic_error("Failed to allocate memory for the msg");
	if(!in.read(msg_, len_) )
	{
		if( msg_ != NULL )
		{
			delete [] msg_;
			msg_ = NULL;
		}
		return;
	}
	msg_[ len_ ] = '\0';

}
binary_reader::market_message::market_message( const boost::uint32_t type, const boost::uint32_t time, const char* const msg )
{	
	type_=type;
	time_=time;
	len_=static_cast<boost::uint32_t>(strlen(msg));
	msg_ = NULL;
	msg_ = new char[len_+1];
	if(!msg_)
		throw logic_error("Failed to allocate memory for the msg");
	memcpy(msg_, msg, len_);
	msg_[ len_ ] = '\0';
}
void binary_reader::market_message::write( std::ofstream& out )
{
	if(!out.write(reinterpret_cast< const char*>(&type_),sizeof(type_)) )
		throw logic_error("can't write 'type'");
	if(!out.write(reinterpret_cast<const char*>(&time_), sizeof(time_)) )
		throw logic_error("can't write 'time'");
	if(!out.write(reinterpret_cast<const char*>(&len_), sizeof(len_)) )
		throw logic_error("can't write 'len'");
	if(!out.write(msg_, len_ ))
		throw logic_error("can't write 'msg'");
}

binary_reader::market_message::~market_message()
{
	if( msg_ != NULL )
	{
		delete [] msg_;
		msg_ = NULL;
	}
}
//

bool binary_reader::market_message::check_time(boost::uint32_t& cur_time) const 
{
	if (cur_time < time_) 
	{
		cur_time = time_;
		return true;
	}
	else
	{
		if( (time_+2) > cur_time )
			return true;
	} 
	return false;

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