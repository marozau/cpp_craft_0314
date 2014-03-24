#include "market_message.h"
#include <cstring>
#include <exception>
#include <iostream>

using namespace std;

 binary_reader::market_message:: market_message( std::ifstream& in )
{

	if(!in.read(reinterpret_cast<char*>(&type_), sizeof(boost:: uint32_t)) )
			throw exception("input is incorrect");
	if(!in.read(reinterpret_cast<char*>(&time_), sizeof(boost:: uint32_t)) )
			throw exception("input is incorrect");
	if(!in.read(reinterpret_cast<char*>(&len_), sizeof(boost:: uint32_t)) )
			throw exception("input is incorrect");
	msg_ = new char[len_];
	if(!in.read(msg_, len_) )
			throw exception("input is incorrect");
}
binary_reader::market_message::market_message( const boost::uint32_t type,
											   const boost::uint32_t time,
											   const char* const msg ) : type_(type), time_(time), len_(static_cast<boost::uint32_t>(strlen(msg)))
{
	msg_=new char[len_ +1];
	memcpy(msg_,msg, len_);
}
void binary_reader::market_message::write( std::ofstream& out )
{
	if(!out.write(reinterpret_cast<char*>(&type_),sizeof(type_)) )
			throw exception("can't write");
	if(!out.write(reinterpret_cast<char*>(&time_), sizeof(time_)) )
			throw exception("can't write");
	if(!out.write(reinterpret_cast<char*>(&len_), sizeof(len_)) )
			throw exception("can't write");
	if(!out.write(msg_, len_ ))
			throw exception("can't write");

}

void binary_reader::market_message::write_txt( std::ofstream& out )
{
	out<<type_<<" "<<time_<<" "<<len_<<" "<<msg_<<endl;
}

binary_reader::market_message::~market_message()
{
	if( msg_ != NULL )
	{
		delete msg_;
	}
}

bool binary_reader::market_message:: check(boost:: uint32_t& T) const 
{
	if (T<time_) 
		{
			T=time_;
			if (type_>=1 && type_<=4)  
				return true;
		}
	else
		{
			if( time_+2>T && type_>=1 && type_<=4 )
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

boost::uint32_t binary_reader::market_message::len() const
{
	return len_;
}
