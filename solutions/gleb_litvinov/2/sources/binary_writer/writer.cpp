#include "writer.h"

namespace io
{
	bin_writer::bin_writer(std::string name)
	{
		out.open( name,std::ios_base::binary);
	}
	bin_writer::~bin_writer()
	{
		if (out.is_open()) out.close();
	}
	bool bin_writer::is_open()const
	{
		return out.is_open();
	}
	void bin_writer::write(const char* const a,size_t length) const
	{
		out.write( a, length );
	}
	
}