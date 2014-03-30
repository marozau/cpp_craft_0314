#include "market_message.h"
#include <cstring>
#include <iostream>

using namespace std;

binary_reader::market_message::market_message( std::ifstream& in )
{
	if(!in.read(reinterpret_cast<char *>(&type_), sizeof(type_))) {
		if (in.eof()) return;
		cerr<<"Input is incorrect type"<<endl;
		return;
	}

    if(!in.read(reinterpret_cast<char *>(&time_), sizeof(time_))) {
		if (in.eof()) return;
		cerr<<"Input is incorrect time"<<endl;
		return;
	}

    if(!in.read(reinterpret_cast<char *>(&len_), sizeof(len_))) {
		if (in.eof()) return;
		cerr<<"Input is incorrect len"<<endl;
		return;
	}
	msg_ = new char[len_+1];
	memset(msg_, 0, len_ +1);
	
	if(!in.read(msg_, len_)) {
		if (in.eof()) return;
		cerr<<"Input is incorrect msg"<<endl;
		return;
	}

}
binary_reader::market_message::market_message( const boost::uint32_t type, const boost::uint32_t time, const char* const msg )
{
	type_=type;
	time_=time;
	len_=static_cast<boost::uint32_t>(strlen(msg));
	msg_ = new char[len_+1];
	memcpy(msg_, msg, len_+1);
}
void binary_reader::market_message::write( std::ofstream& out )
{
	if(!out.write(reinterpret_cast<char *>(&type_), sizeof(type_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
	if(!out.write(reinterpret_cast<char *>(&time_), sizeof(time_))) {
		cerr<<"I can not write data"<<endl;
		return;
	}
	if(!out.write(reinterpret_cast<char *>(&len_), sizeof(len_))) {
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

size_t binary_reader::market_message::type() const
{
	return static_cast<size_t>(type_);
}
size_t binary_reader::market_message::time() const
{
	return static_cast<size_t>(time_);
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
	return (sizeof(type_)+sizeof(time_)+sizeof(len_)+len_);
}
binary_reader::market_message::market_message(const market_message & a): type_(a.type_),time_(a.time_),len_(a.len_)
{
	msg_ = new char[len_+1];
	memcpy(msg_, a.msg_, len_+1);
}
binary_reader::market_message & binary_reader::market_message::operator = (const market_message & a)
{
	if (this!=& a){
		type_=a.type_;
		time_=a.time_;
		len_=a.len_;
		delete [] msg_;
		msg_=NULL;
		msg_ = new char[len_+1];
		memcpy(msg_, a.msg_, len_+1);
	}
	return *this;
}