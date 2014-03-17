#include <iostream>
#include <fstream>
#include <boost/cstdint.hpp>
#include <vector>
#include <map>

typedef boost::uint32_t int32;

struct Sdata {
	int32 TYPE;
	int32 TIME;
	int32 LEN;
	char *MSG;

	Sdata() :
			TYPE(0), TIME(0), LEN(0), MSG(NULL) {
	}
};

typedef std::vector<Sdata*> vector;
typedef std::map<const int32, vector*> map;

//Check buffer limit
bool checkBuffer(vector *vect, int32 time, const int32 limit) {
	int32 count = 0;

	for (vector::iterator it = vect->begin(); it != vect->end(); ++it) {
		if ((*it)->TIME == time) count++;
	}

	if (count * sizeof(Sdata) > limit)
		return false;
	else
		return true;
}

//Created associative array for storage of vectors, which contain requests of each type
void handlerOfData(std::fstream &fileIn, map &typesOfMsg, const int32 size, const int32 limit) {

	Sdata *request = new Sdata();

	fileIn.read(reinterpret_cast<char*>(&request->TYPE), sizeof(int32));
	if (!fileIn) {
		std::cout << "There is no data in input file" << std::endl;
		fileIn.close();
		exit(1);
	}
	fileIn.read(reinterpret_cast<char*>(&request->TIME), sizeof(int32));
	fileIn.read(reinterpret_cast<char*>(&request->LEN), sizeof(int32));
	request->MSG = new char[request->LEN];
	fileIn.read(reinterpret_cast<char*>(request->MSG), request->LEN * sizeof(char));

	do {
		if (request->TYPE <= size && typesOfMsg.find(request->TYPE) == typesOfMsg.end())
			typesOfMsg[request->TYPE] = new vector;
		if (request->TYPE <= size && (typesOfMsg[request->TYPE]->empty()
			|| checkBuffer(typesOfMsg[request->TYPE], request->TIME, limit))) {
			typesOfMsg[request->TYPE]->push_back(request);
		}
		request = new Sdata();
		fileIn.read(reinterpret_cast<char*>(&request->TYPE), sizeof(int32));
		fileIn.read(reinterpret_cast<char*>(&request->TIME), sizeof(int32));
		fileIn.read(reinterpret_cast<char*>(&request->LEN), sizeof(int32));
		request->MSG = new char[request->LEN];
		fileIn.read(reinterpret_cast<char*>(request->MSG), request->LEN * sizeof(char));
	} while (fileIn);
	delete request;
}

//Computed mean number of messages of all seconds for each request type
void meanOfEachMsg(std::fstream &fileOut, map &typesOfMsg, const int32 size) {

	int32 sec = 0;
	double mean = 0;
	int time = -1;

	for (int32 i = 0; i < size; i++) {
		if (typesOfMsg.find(i) != typesOfMsg.end()) {
			for (vector::iterator it = typesOfMsg[i]->begin(); it != typesOfMsg[i]->end(); ++it) {
				if (static_cast<int>((*it)->TIME) > time) {
					time = (*it)->TIME;
					sec++;
				}
			}
			fileOut.write(reinterpret_cast<char*>(&i), sizeof(int32));
			mean = static_cast<double>(typesOfMsg[i]->size()) / sec;
			fileOut.write(reinterpret_cast<char*>(&mean), sizeof(double));
			time = -1;
			sec = 0;
		}
	}
}

//Console check for result data
void concoleCheckForOutput(std::fstream &fileIn){
	double mean=0;
	int32 type=0;

	fileIn.read(reinterpret_cast<char*>(&type), sizeof(int32));
	if (!fileIn) {
		std::cout << "There is no data in output file" << std::endl;
		fileIn.close();
		exit(1);
	}
	fileIn.read(reinterpret_cast<char*>(&mean), sizeof(double));

	do {
	    std::cout<<type<<" "<<mean<<std::endl;

		fileIn.read(reinterpret_cast<char*>(&type), sizeof(int32));
		fileIn.read(reinterpret_cast<char*>(&mean), sizeof(double));
	} while (fileIn);
}

int main(int argc, char **argv) {

	std::fstream fileIn;
	fileIn.open( BINARY_DIR "/input.txt", std::ios::binary | std::ios::in);
	if (!fileIn) {
		std::cout << "Error path for input.txt" << std::endl;
		fileIn.close();
		exit(1);
	}

	const int32 size = 100000;
	const int32 limit = 2048;
	map typesOfMsg;
	handlerOfData(fileIn, typesOfMsg, size, limit);

	std::fstream fileOut;
	fileOut.open( BINARY_DIR "/output.txt", std::ios::binary | std::ios::out);
	if (!fileOut) {
		std::cout << "Error path for output.txt" << std::endl;
		fileIn.close();
		fileOut.close();
		exit(1);
	}

	meanOfEachMsg(fileOut, typesOfMsg, size);

	for (int32 i = 0; i < typesOfMsg.size(); i++) {
		if (typesOfMsg.find(i) != typesOfMsg.end()) {
			for (int32 j = 0; j < typesOfMsg[i]->size(); j++) {
				delete[] typesOfMsg[i]->at(j)->MSG;
				delete typesOfMsg[i]->at(j);
			}
			delete typesOfMsg[i];
		}
	}

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

