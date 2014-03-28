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

	Sdata() :
			type(0), time(0), len(0), msg(NULL) {
	}

	bool readData(std::ifstream * const fileIn);
	bool writeData(std::ofstream * const fileOut);
};

bool Sdata::readData(std::ifstream * const fileIn) {
	fileIn->read(reinterpret_cast<char*>(&type), sizeof(uint_32));
	fileIn->read(reinterpret_cast<char*>(&time), sizeof(uint_32));
	fileIn->read(reinterpret_cast<char*>(&len), sizeof(uint_32));
	msg = new char[len + 1];
	msg[len] = '\0';
	fileIn->read(reinterpret_cast<char*>(msg), (len) * sizeof(char));
	if (!*fileIn)
		return false;
	return true;
}

bool Sdata::writeData(std::ofstream * const fileOut) {
	fileOut->write(reinterpret_cast<char*>(&type), sizeof(uint_32));
	fileOut->write(reinterpret_cast<char*>(&time), sizeof(uint_32));
	fileOut->write(reinterpret_cast<char*>(&len), sizeof(uint_32));
	fileOut->write(reinterpret_cast<char*>(msg), (len) * sizeof(char));
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
	const uint_32 from = 0;
	const uint_32 to = 5;
	const uint_128 limit = 10000000000000000;
	uint_128 count = 0;

	do {
		count++;
		if ((int) request->time > (time - 2) && request->type > from && request->type < to) {
			if ((int) request->time > time)
				time = request->time;
			if (!request->writeData(fileOut)) {
				std::cout << "Write error" << std::endl;
				fileIn->close();
				fileOut->close();
				delete fileIn;
				delete fileOut;
				return;
			}
		}
		delete[] request->msg;
		delete request;
		request = new Sdata();
	} while ((count + 1) < limit && request->readData(fileIn));
	delete[] request->msg;
	delete request;

	fileIn->close();
	fileOut->close();

	delete fileIn;
	delete fileOut;
}

//Console check for result data
void consoleCheckForOutput(std::ifstream *const fileIn){
	Sdata *request = new Sdata();

	if(!request->readData(fileIn)){
			std::cout << "There is no data in input file" << std::endl;
			return;
		}

	do {
	    std::cout<<request->type<<" "<<request->time<<" "<<request->len<<" "<<request->msg<<std::endl;
		delete[] request->msg;
		delete request;
		request = new Sdata();
	} while (request->readData(fileIn));
	delete[] request->msg;
	delete request;
}

int main(int argc, char **argv) {
	boost::thread_group threads;

	const std::string nameIn = "/input_";
	const std::string nameOut = "/output_";
	const std::string format = ".txt";
	std::string number = "000";
	const uint_32 var = number.size();
	std::string buf;

	for (uint_32 i = 1; i <= 999; i++) {
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

	/*number = "000";

	for (uint_32 i = 1; i <= 999; i++) {
			buf = boost::lexical_cast<std::string>(i);
			number.insert(number.size() - buf.size(), buf);
			number.erase(var);

			std::ifstream *fileIn = new std::ifstream( BINARY_DIR (nameOut + number + format).c_str(), std::ios::binary);

			consoleCheckForOutput(fileIn);

			std::cout<<std::endl<<std::endl<<std::endl;

			fileIn->close();
			delete fileIn;
	}*/

	return 0;
}

