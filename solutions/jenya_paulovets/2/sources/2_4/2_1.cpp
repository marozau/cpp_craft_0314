#include <iostream>
#include <fstream>
#include <boost/cstdint.hpp>
#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::uint128_t bigInt;
typedef boost::uint32_t int32;

struct Sdata {
	int32 TYPE;
	int32 TIME;
	int32 LEN;
	char *MSG;

	Sdata():TYPE(0), TIME(0), LEN(0), MSG(NULL){
	}

	bool readData(std::fstream &fileIn);
	bool writeData(std::fstream &fileOut);
};

bool Sdata::readData(std::fstream &fileIn){
	fileIn.read(reinterpret_cast<char*>(&TYPE), sizeof(int32));
	fileIn.read(reinterpret_cast<char*>(&TIME), sizeof(int32));
	fileIn.read(reinterpret_cast<char*>(&LEN), sizeof(int32));
	MSG = new char[LEN+1];
	fileIn.read(reinterpret_cast<char*>(MSG), (LEN) * sizeof(char));
	if(!fileIn)return false;
	return true;
}

bool Sdata::writeData(std::fstream &fileOut){
	fileOut.write(reinterpret_cast<char*>(&TYPE), sizeof(int32));
	fileOut.write(reinterpret_cast<char*>(&TIME), sizeof(int32));
	fileOut.write(reinterpret_cast<char*>(&LEN), sizeof(int32));
	fileOut.write(reinterpret_cast<char*>(MSG), (LEN) * sizeof(char));
	if(!fileOut)return false;
	return true;
}

//Step by step data is readed, handled, written by function in output file,
//while there isn't eof flag in input file or while counter <= than limit
void searchActualData(std::fstream &fileIn, std::fstream &fileOut, const bigInt &limit) {

	Sdata *request = new Sdata();

	if(!request->readData(fileIn)){
		std::cout << "There is no data in input file" << std::endl;
		fileIn.close();
		fileOut.close();
		exit(1);
	}

	int time = 0;
	const int32 from = 0;
	const int32 to = 5;
	bigInt count = 0;

	do {
		count++;
		if ((int) request->TIME > (time - 2) && request->TYPE > from && request->TYPE < to) {
			if ((int) request->TIME > time) time = request->TIME;
			if(!request->writeData(fileOut)){
				std::cout << "Write error" << std::endl;
				fileIn.close();
				fileOut.close();
				exit(1);
			}
		}
		delete[] request->MSG;
		delete request;
		request = new Sdata();
	} while ((count+1) < limit && request->readData(fileIn));
	delete[] request->MSG;
	delete request;
}

//Console check for result data
void concoleCheckForOutput(std::fstream &fileIn){
	Sdata *request = new Sdata();

	if(!request->readData(fileIn)){
			std::cout << "There is no data in input file" << std::endl;
			fileIn.close();
			exit(1);
		}

	do {
	    std::cout<<request->TYPE<<" "<<request->TIME<<" "<<request->LEN<<" "<<request->MSG<<std::endl;
		delete[] request->MSG;
		delete request;
		request = new Sdata();
	} while (request->readData(fileIn));
	delete[] request->MSG;
	delete request;
}

int main(int argc, char **argv) {

	std::fstream fileIn;
	fileIn.open( BINARY_DIR "/input.txt", std::ios::binary | std::ios::in);
	if (!fileIn) {
		std::cout << "Error path for input.txt" << std::endl;
		fileIn.close();
		exit(1);
	}

	std::fstream fileOut;
	fileOut.open( BINARY_DIR "/output.txt", std::ios::binary | std::ios::out);
	if (!fileOut) {
		std::cout << "Error path for output.txt" << std::endl;
		fileIn.close();
		fileOut.close();
		exit(1);
	}

	const bigInt limit = 10000000000000000;
	searchActualData(fileIn, fileOut, limit);

	fileIn.close();
	fileOut.close();

	/*
	fileIn.open( BINARY_DIR "/output.txt", std::ios::binary | std::ios::in);
		if (!fileIn) {
			std::cout << "Error path for output.txt" << std::endl;
			fileIn.close();
			exit(1);
		}

	concoleCheckForOutput(fileIn);

	fileIn.close();*/

	return 0;
}

