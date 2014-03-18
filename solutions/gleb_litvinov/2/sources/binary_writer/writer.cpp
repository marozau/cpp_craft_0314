#include "writer.h"

namespace io
{
	bin_writer::bin_writer(std::string name)
	{
		out.open( BINARY_DIR "/"+name,std::ios_base::binary);
	}
	bin_writer::~bin_writer()
	{
		if (out.is_open()) out.close();
	}
	bool bin_writer::is_open()
	{
		return out.is_open();
	}
	void bin_writer::write(char* const a,size_t length)
	{
		if (!length) length=std::strlen(a);
		out.write( a, length );
	}
	void bin_writer::write(const std::string a)
	{
		out.write( a.c_str(),0);
	}
}