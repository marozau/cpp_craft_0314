#include "market_message.h"
#include <cstring>
#include <iostream>

using namespace std;

binary_reader::market_message::market_message( std::ifstream& in )
{
	if(!in.read((char *)&type_, sizeof(type_))) {
		cerr<<"Input is incorrect"<<endl;
		return;
	}

    if(!in.read((char *)&time_, sizeof(time_))) {
		cerr<<"Input is incorrect"<<endl;
		return;
	}

    if(!in.read((char *)&len_, sizeof(len_))) {
		cerr<<"Input is incorrect"<<endl;
		return;
	}
	msg_ = new char[len_];
	memset(msg_, 0, len_ );
	if(!in.read((char *)msg_, len_)) {
		cerr<<"Input is incorrect"<<endl;
		return;
	}

}
binary_reader::market_message::market_message( const boost::uint32_t type, const boost::uint32_t time, const char* const msg )
{
	type_=type;
	time_=time;
	len_=static_cast<boost::uint32_t>(strlen(msg));
	msg_ = new char[len_ ];
	memcpy(msg_, msg, len_);
}
void binary_reader::market_message::write( std::ofstream& out )
{
	if(!out.write((char *)&type_, sizeof(type_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
	if(!out.write((char *)&time_, sizeof(time_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
	if(!out.write((char *)&len_, sizeof(len_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
	if(!out.write(msg_, len_)) {
		cerr<<"I can not write data"<<endl;
		return;
	}
	
}

binary_reader::market_message::~market_message()
{
	if (msg_){
		delete [] msg_;
		msg_ = NULL;
	}
}

boost::uint32_t binary_reader::market_message::type() const
{
	return type_;
}
boost::uint32_t binary_reader::market_message::time() const
{
	return time_;
}
boost::uint32_t binary_reader::market_message::len() const
{
	return len_;
}
const char* const binary_reader::market_message::msg() const
{
	return msg_;
}
size_t binary_reader::market_message::size() const
{
	return (sizeof(type_)+sizeof(time_)+sizeof(len_)+sizeof(msg_));
}
binary_reader::market_message::market_message(const market_message & a): type_(a.type_),time_(a.time_),len_(a.len_)
{
	msg_ = new char[len_];
	memcpy(msg_, a.msg_, len_);
}
binary_reader::market_message & binary_reader::market_message::operator = (const market_message & a)
{
	if (this!=& a){
		type_=a.type_;
		time_=a.time_;
		len_=a.len_;
		delete [] msg_;
		msg_=NULL;
		msg_ = new char[len_];
		memcpy(msg_, a.msg_, len_);
	}
	return *this;
}