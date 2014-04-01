#include "market_message.h"
#include <cstring>
#include <exception>
#include <iostream>



using namespace std;

 binary_reader::market_message:: market_message( std::ifstream& in )
{

	if(!in.read(reinterpret_cast<char*>(&type_), sizeof(boost:: uint32_t)) )
		throw logic_error("input is incorrect");
	if(!in.read(reinterpret_cast<char*>(&time_), sizeof(boost:: uint32_t)) )
			throw logic_error("input is incorrect");
	if(!in.read(reinterpret_cast<char*>(&len_), sizeof(boost:: uint32_t)) )
			throw logic_error("input is incorrect");
	msg_ = new char[len_];
	if(!in.read(msg_, len_) )
			throw logic_error("input is incorrect");
}
binary_reader::market_message::market_message( const boost::uint32_t type,
											   const boost::uint32_t time,
											   const char* const msg ) : type_(type), time_(time), len_(static_cast<boost::uint32_t>(strlen(msg)))
{
	msg_=new char[len_ +1];
	memcpy(msg_,msg, len_);
}
void binary_reader::market_message::write( std::ofstream& out ) const
{
	if(!out.write(reinterpret_cast< const char*>(&type_),sizeof(type_)) )
			throw logic_error("can't write");
	if(!out.write(reinterpret_cast<const char*>(&time_), sizeof(time_)) )
			throw logic_error("can't write");
	if(!out.write(reinterpret_cast<const char*>(&len_), sizeof(len_)) )
			throw logic_error("can't write");
	if(!out.write(msg_, len_ ))
			throw logic_error("can't write");

}

void binary_reader::market_message::write_txt( std::ofstream& out ) const
{
	out << type_ << " " << time_ << " " << len_ << " " << msg_ << endl;
}

binary_reader::market_message::~market_message()
{
	if( msg_ != NULL )
	{
		delete [] msg_;
	}
}

bool binary_reader::market_message:: check(boost:: uint32_t& curr_time) const 
{
	if (curr_time<time_) 
	{
		curr_time=time_;
		if (type_>=1 && type_<=4)  
			return true;
	}
	else
	{
		if( time_+2>curr_time && type_>=1 && type_<=4 )
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


size_t  binary_reader::market_message:: get_size() const
{
	return (sizeof(type_) + sizeof(time_) + sizeof(len_) + sizeof(char)*len_);
}

bool binary_reader::market_message:: check_size( map <boost:: uint32_t, size_t> & size) const 
{
	return ( ( size[type_] + get_size()) < binary_reader:: market_message::buffer_size );
}