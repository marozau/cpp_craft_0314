#include "read_write_impl.h"

void read_write_impl::read(std::ifstream & in, char * t, size_t const n)
{
	in.read(t, n);
}

void read_write_impl::write(std::ofstream & out, char const * const t, size_t const n)
{
	out.write(t, n);
}
