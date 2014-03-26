#ifndef _BINARY_READER_READ_AND_WRITE_H_
#define _BINARY_READER_READ_AND_WRITE_H_

#include <fstream>

namespace read_and_write
{
	template<class T>
	void read_binary(std::ifstream& in, T& t, const size_t len = sizeof(T))
	{
		in.read(reinterpret_cast<char*>(&t), len);
	}

	template<class T>
	void write_binary(std::ofstream& out, T& t, const size_t len = sizeof(T))
	{
		out.write(reinterpret_cast<const char*>(&t), len);
	}
}

#endif // _BINARY_READER_READ_AND_WRITE_H_
