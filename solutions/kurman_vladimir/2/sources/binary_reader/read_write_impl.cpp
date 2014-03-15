#include "read_write_impl.h"

void read_write_impl::read(std::ifstream & in, char * t, size_t n)
{
	in.read(reinterpret_cast<char*>(t), n);
}

void read_write_impl::write(std::ofstream & out, char const * const t, unsigned int n)
{
	out.write(reinterpret_cast<char const * const>(t), n);
}
