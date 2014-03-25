#include <iostream>
#include <fstream>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/cstdint.hpp>
#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::uint128_t bigInt;
typedef boost::uint32_t int32;

struct Sdata {
	int32 TYPE;
	int32 TIME;
	int32 LEN;
	char *MSG;

	Sdata() :
			TYPE(0), TIME(0), LEN(0), MSG(NULL) {
	}

	bool readData(std::ifstream * const fileIn);
	bool writeData(std::ofstream * const fileOut);
};

bool Sdata::readData(std::ifstream * const fileIn) {
	fileIn->read(reinterpret_cast<char*>(&TYPE), sizeof(int32));
	fileIn->read(reinterpret_cast<char*>(&TIME), sizeof(int32));
	fileIn->read(reinterpret_cast<char*>(&LEN), sizeof(int32));
	MSG = new char[LEN + 1];
	MSG[LEN] = '\0';
	fileIn->read(reinterpret_cast<char*>(MSG), (LEN) * sizeof(char));
	if (!*fileIn)
		return false;
	return true;
}

bool Sdata::writeData(std::ofstream * const fileOut) {
	fileOut->write(reinterpret_cast<char*>(&TYPE), sizeof(int32));
	fileOut->write(reinterpret_cast<char*>(&TIME), sizeof(int32));
	fileOut->write(reinterpret_cast<char*>(&LEN), sizeof(int32));
	fileOut->write(reinterpret_cast<char*>(MSG), (LEN) * sizeof(char));
	if (!*fileOut)
		return false;
	return true;
}

//Step by step data is readed, handled, written by function in output file,
//while there isn't eof flag in input file or while counter <= than limit
void searchActualData(std::ifstream * const fileIn, std::ofstream * const fileOut) {
	Sdata *request = new Sdata();

	if (!request->readData(fileIn)) {
		std::cout << "There is no data in input file" << std::endl;
		fileIn->close();
		fileOut->close();
		delete fileIn;
		delete fileOut;
		return;
	}

	int time = 0;
	const int32 from = 0;
	const int32 to = 5;
	const bigInt limit = 10000000000000000;
	bigInt count = 0;

	do {
		count++;
		if ((int) request->TIME > (time - 2) && request->TYPE > from && request->TYPE < to) {
			if ((int) request->TIME > time)
				time = request->TIME;
			if (!request->writeData(fileOut)) {
				std::cout << "Write error" << std::endl;
				fileIn->close();
				fileOut->close();
				delete fileIn;
				delete fileOut;
				return;
			}
		}
		delete[] request->MSG;
		delete request;
		request = new Sdata();
	} while ((count + 1) < limit && request->readData(fileIn));
	delete[] request->MSG;
	delete request;

	fileIn->close();
	fileOut->close();

	delete fileIn;
	delete fileOut;
}

int main(int argc, char **argv) {
	boost::thread_group threads;

	const std::string nameIn = "/input_";
	const std::string nameOut = "/output_";
	const std::string format = ".txt";
	std::string number = "000";
	const int32 var = number.size();
	std::string buf;

	for (int32 i = 1; i <= 999; i++) {
		buf = boost::lexical_cast<std::string>(i);
		number.insert(number.size() - buf.size(), buf);
		number.erase(var);

		std::ifstream *fileIn = new std::ifstream( BINARY_DIR (nameIn + number + format).c_str(), std::ios::binary);
		if (!*fileIn) {
			std::cout << "Error path for " << nameIn + number + format << std::endl;
			fileIn->close();
			delete fileIn;
			continue;
		}
		std::ofstream *fileOut = new std::ofstream( BINARY_DIR (nameOut + number + format).c_str(), std::ios::binary);
		if (!*fileOut) {
			std::cout << "Error path for " << nameOut + number + format << std::endl;
			fileIn->close();
			fileOut->close();
			delete fileIn;
			delete fileOut;
			continue;
		}
		threads.create_thread(boost::bind(&searchActualData, fileIn, fileOut));
	}

	threads.join_all();

	return 0;
}

