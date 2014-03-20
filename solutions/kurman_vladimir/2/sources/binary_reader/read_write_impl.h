#ifndef _READ_WRITE_IMPL_H_
#define _READ_WRITE_IMPL_H_

#include <fstream>

namespace read_write_impl
{
	template <class T>
	void read(std::ifstream & in, T & t)
	{
		in.read(reinterpret_cast<char*>(&t), sizeof(t));
	}
	void read(std::ifstream & in, char * t, size_t const n);
	template <class T>
	void write(std::ofstream & out, T const & t)
	{
		out.write(reinterpret_cast<char const*>(&t), sizeof(t));
	}
	void write(std::ofstream & out, char const * const t, size_t const n);
}

#endif // _READ_WRITE_IMPL_H_
