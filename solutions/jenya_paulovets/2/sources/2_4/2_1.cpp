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
};

//Step by step data is readed, handled, written by function in output file,
//while there isn't eof flag in input file or while counter <= than limit
void searchActualData(std::fstream &fileIn, std::fstream &fileOut, const bigInt &limit) {

	Sdata *request = new Sdata();
	bigInt count = 0;

	fileIn.read(reinterpret_cast<char*>(&request->TYPE), sizeof(int32));
	if (!fileIn) {
		std::cout << "There is no data in input file" << std::endl;
		fileIn.close();
		fileOut.close();
		exit(1);
	}
	count++;
	fileIn.read(reinterpret_cast<char*>(&request->TIME), sizeof(int32));
	fileIn.read(reinterpret_cast<char*>(&request->LEN), sizeof(int32));
	request->MSG = new char[request->LEN];
	fileIn.read(reinterpret_cast<char*>(request->MSG), request->LEN * sizeof(char));

	int time = 0;

	do {
		if ((int) request->TIME > (time - 2) && request->TYPE > 0 && request->TYPE < 5) {
			if ((int) request->TIME > time) time = request->TIME;
			fileOut.write(reinterpret_cast<char*>(&request->TYPE), sizeof(int32));
			if (!fileOut) {
				std::cout << "Write error" << std::endl;
				fileIn.close();
				fileOut.close();
				exit(1);
			}
			fileOut.write(reinterpret_cast<char*>(&request->TIME), sizeof(int32));
			fileOut.write(reinterpret_cast<char*>(&request->LEN), sizeof(int32));
			fileOut.write(reinterpret_cast<char*>(request->MSG), request->LEN * sizeof(char));
		}
		delete[] request->MSG;
		delete request;
		request = new Sdata();
		fileIn.read(reinterpret_cast<char*>(&request->TYPE), sizeof(int32));
		fileIn.read(reinterpret_cast<char*>(&request->TIME), sizeof(int32));
		fileIn.read(reinterpret_cast<char*>(&request->LEN), sizeof(int32));
		request->MSG = new char[request->LEN];
		fileIn.read(reinterpret_cast<char*>(request->MSG), request->LEN * sizeof(char));
		count++;
	} while (count < limit && fileIn);
	delete[] request->MSG;
	delete request;
}

//Console check for result data
void concoleCheckForOutput(std::fstream &fileIn){
	Sdata *request = new Sdata();

	fileIn.read(reinterpret_cast<char*>(&request->TYPE), sizeof(int32));
	if (!fileIn) {
		std::cout << "There is no data in output file" << std::endl;
		fileIn.close();
		exit(1);
	}
	fileIn.read(reinterpret_cast<char*>(&request->TIME), sizeof(int32));
	fileIn.read(reinterpret_cast<char*>(&request->LEN), sizeof(int32));
	request->MSG = new char[request->LEN];
	fileIn.read(reinterpret_cast<char*>(request->MSG), request->LEN * sizeof(char));

	do {
	    std::cout<<request->TYPE<<" "<<request->TIME<<" "<<request->LEN<<" "<<request->MSG<<std::endl;
		delete[] request->MSG;
		delete request;
		request = new Sdata();
		fileIn.read(reinterpret_cast<char*>(&request->TYPE), sizeof(int32));
		fileIn.read(reinterpret_cast<char*>(&request->TIME), sizeof(int32));
		fileIn.read(reinterpret_cast<char*>(&request->LEN), sizeof(int32));
		request->MSG = new char[request->LEN];
		fileIn.read(reinterpret_cast<char*>(request->MSG), request->LEN * sizeof(char));
	} while (fileIn);
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

	fileIn.open( BINARY_DIR "/output.txt", std::ios::binary | std::ios::in);
		if (!fileIn) {
			std::cout << "Error path for output.txt" << std::endl;
			fileIn.close();
			exit(1);
		}

	concoleCheckForOutput(fileIn);

	fileIn.close();

	return 0;
}

