#include "reader.h"

namespace io
{
	bin_reader::bin_reader(std::string name)
	{
		in.open( SOURCE_DIR "/"+name,std::ios_base::binary);
	}
	bin_reader::~bin_reader()
	{
		if (in.is_open()) in.close();
	}
	bool bin_reader::is_open()
	{
		return in.is_open();
	}
	void bin_reader::read(char* const a,size_t length)
	{
		in.read( a, length );
	}
	bool bin_reader::eof()
	{
		return !in;
	}
}