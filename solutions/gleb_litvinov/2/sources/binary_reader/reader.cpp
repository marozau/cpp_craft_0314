#include "reader.h"
#include <string>

namespace io
{
	std::string bin_reader::read(const size_t length)
	{
		char *c;
		c = new char [length+1];
		std::string tmp;
		in.read(c,length);
		tmp.assign(c,c+length);
		delete []c;
		return tmp;
	}
	bin_reader::bin_reader(const std::string& name)
	{
		in.open(name,std::ios_base::binary);
	}
	bin_reader::~bin_reader()
	{
		if (in.is_open()) in.close();
	}
	bool bin_reader::is_open()const
	{
		return in.is_open();
	}
	void bin_reader::read(char* const a,const size_t length)
	{
		in.read( a, length );
	}
	bool bin_reader::eof() const
	{
		return !in;
	}
}