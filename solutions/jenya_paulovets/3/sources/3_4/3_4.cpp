#include <iostream>
#include <fstream>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/cstdint.hpp>
#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::uint128_t uint_128;
typedef boost::uint32_t uint_32;

struct Sdata {
	uint_32 type;
	uint_32 time;
	uint_32 len;
	char *msg;

	Sdata() : type(0), time(0), len(0), msg(NULL)
	{}

	bool readData(std::ifstream * const fileIn);
	bool writeData(std::ofstream * const fileOut) const;

	~Sdata()
	{
		delete[] msg;
	}
};

bool Sdata::readData(std::ifstream * const fileIn)
{
	fileIn->read(reinterpret_cast<char*>(&type), sizeof(uint_32));
	if(fileIn->eof()) return false;
	fileIn->read(reinterpret_cast<char*>(&time), sizeof(uint_32));
	fileIn->read(reinterpret_cast<char*>(&len), sizeof(uint_32));
	msg = new char[len + 1];
	msg[len] = '\0';
	fileIn->read(reinterpret_cast<char*>(msg), (len) * sizeof(char));
	if (!*fileIn)
		return false;
	return true;
}

bool Sdata::writeData(std::ofstream * const fileOut) const
{
	fileOut->write(reinterpret_cast<const char*>(&type), sizeof(uint_32));
	fileOut->write(reinterpret_cast<const char*>(&time), sizeof(uint_32));
	fileOut->write(reinterpret_cast<const char*>(&len), sizeof(uint_32));
	fileOut->write(reinterpret_cast<const char*>(msg), (len) * sizeof(char));
	if (!*fileOut)
		return false;
	return true;
}

//Step by step data is readed, handled, written by function in output file,
//while there isn't eof flag in input file or while counter <= than limit
void searchActualData(std::ifstream * const fileIn, std::ofstream * const fileOut)
{
	Sdata *request = new Sdata();

	if (!request->readData(fileIn))
	{
		std::cout << "There is no data in input file" << std::endl;
		fileIn->close();
		fileOut->close();
		delete request;
		delete fileIn;
		delete fileOut;
		return;
	}

	uint32_t time = 0;
	const uint_32 from = 0;
	const uint_32 to = 5;
	const uint_128 limit = 10000000000000000;
	const uint_32 dif = 2;
	uint_128 count = 0;

	do {
		count++;
		if ((request->time + dif) > time && request->type > from && request->type < to)
		{
			if (request->time > time)
				time = request->time;
			if (!request->writeData(fileOut))
			{
				std::cout << "Write error" << std::endl;
				fileIn->close();
				fileOut->close();
				delete request;
				delete fileIn;
				delete fileOut;
				return;
			}
		}
		delete request;
		request = new Sdata();
	} while ((count + 1) < limit && request->readData(fileIn));
	delete request;

	fileIn->close();
	fileOut->close();

	delete fileIn;
	delete fileOut;
}

int main(int argc, char **argv)
{
	boost::thread_group threads;

	const std::string nameIn = "/input_";
	const std::string nameOut = "/output_";
	const std::string format = ".txt";

	for (uint_32 i = 1; i <= 999; i++) {
		const std::string number = boost::str(boost::format("%03u") % i);

		const std::string in_path = std::string(BINARY_DIR).append(nameIn).append(number).append(format);
		const std::string out_path = std::string(BINARY_DIR).append(nameOut).append(number).append(format);

		std::ifstream *fileIn = new std::ifstream(in_path.c_str(), std::ios::binary);
		if (!*fileIn)
		{
			std::cout << "There is no file " << nameIn + number + format << std::endl;
			delete fileIn;
			continue;
		}
		std::ofstream *fileOut = new std::ofstream(out_path.c_str(), std::ios::binary);
		if (!*fileOut)
		{
			std::cout << "There is no file " << nameOut + number + format << std::endl;
			fileIn->close();
			delete fileIn;
			delete fileOut;
			continue;
		}
		threads.create_thread(boost::bind(&searchActualData, fileIn, fileOut));
	}

	threads.join_all();

	return 0;
}

