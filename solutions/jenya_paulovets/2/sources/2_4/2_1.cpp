#include <iostream>
#include <fstream>
#include <boost/cstdint.hpp>
#include <boost/multiprecision/cpp_int.hpp>


typedef boost::multiprecision::uint128_t uint_128;
typedef boost::uint32_t uint_32;

struct Sdata
{
	uint_32 type;
	uint_32 time;
	uint_32 len;
	char *msg;

	Sdata():type(0), time(0), len(0), msg(NULL)
	{}

	bool readData(std::fstream &fileIn);
	bool writeData(std::fstream &fileOut) const;
};

bool Sdata::readData(std::fstream &fileIn)
{
	fileIn.read(reinterpret_cast<char*>(&type), sizeof(uint_32));
	fileIn.read(reinterpret_cast<char*>(&time), sizeof(uint_32));
	fileIn.read(reinterpret_cast<char*>(&len), sizeof(uint_32));
	msg = new char[len+1];
	msg[len] = '\0';
	fileIn.read(reinterpret_cast<char*>(msg), (len) * sizeof(char));
	if(!fileIn)return false;
	return true;
}

bool Sdata::writeData(std::fstream &fileOut) const
{
	fileOut.write(reinterpret_cast<const char*>(&type), sizeof(uint_32));
	fileOut.write(reinterpret_cast<const char*>(&time), sizeof(uint_32));
	fileOut.write(reinterpret_cast<const char*>(&len), sizeof(uint_32));
	fileOut.write(reinterpret_cast<const char*>(msg), (len) * sizeof(char));
	if(!fileOut)return false;
	return true;
}

//Step by step data is readed, handled, written by function in output file,
//while there isn't eof flag in input file or while counter <= than limit
void searchActualData(std::fstream &fileIn, std::fstream &fileOut, const uint_128 &limit)
{

	Sdata *request = new Sdata();

	if(!request->readData(fileIn))
	{
		std::cout << "There is no data in input file" << std::endl;
		fileIn.close();
		fileOut.close();
		exit(1);
	}

	int time = 0;
	const uint_32 from = 0;
	const uint_32 to = 5;
	const uint_32 dif = 2;
	uint_128 count = 0;

	do
	{
		count++;
		if (static_cast<int> (request->time) > (time - static_cast<int>(dif)) && request->type > from && request->type < to)
		{
			if (static_cast<int> (request->time) > time) time = request->time;
			if(!request->writeData(fileOut))
			{
				std::cout << "Write error" << std::endl;
				fileIn.close();
				fileOut.close();
				exit(1);
			}
		}
		delete[] request->msg;
		delete request;
		request = new Sdata();
	} while ((count+1) < limit && request->readData(fileIn));
	delete[] request->msg;
	delete request;
}

int main(int argc, char **argv)
{

	std::fstream fileIn;
	fileIn.open( BINARY_DIR "/input.txt", std::ios::binary | std::ios::in);
	if (!fileIn)
	{
		std::cout << "Error path for input.txt" << std::endl;
		fileIn.close();
		exit(1);
	}

	std::fstream fileOut;
	fileOut.open( BINARY_DIR "/output.txt", std::ios::binary | std::ios::out);
	if (!fileOut)
	{
		std::cout << "Error path for output.txt" << std::endl;
		fileIn.close();
		fileOut.close();
		exit(1);
	}

	const uint_128 limit = 10000000000000000;
	searchActualData(fileIn, fileOut, limit);

	fileIn.close();
	fileOut.close();

	return 0;
}

