#include <iostream>
#include <fstream>
#include <boost/cstdint.hpp>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
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

	bool readData(std::ifstream * const fileIn);
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

typedef std::vector<Sdata*> vector;
typedef std::map<const int32, vector*> map;

//Check buffer limit
bool checkBuffer(vector * const vect, const int32 time, const int32 limit) {
	int32 count = 0;

	for (vector::iterator it = vect->begin(); it != vect->end(); ++it) {
		if ((*it)->TIME == time)
			count++;
	}

	if (count * sizeof(Sdata) > limit)
		return false;
	else
		return true;
}

//Created associative array for storage of vectors, which contain requests of each type
bool handlerOfData(std::ifstream * const fileIn, map * const typesOfMsg, const int32 size, const int32 limit) {

	Sdata *request = new Sdata();

	if (!request->readData(fileIn)) {
		std::cout << "There is no data in input file" << std::endl;
		fileIn->close();
		delete fileIn;
		return false;
	}

	do {
		if (request->TYPE <= size && typesOfMsg->find(request->TYPE) == typesOfMsg->end())
			(*typesOfMsg)[request->TYPE] = new vector;
		if (request->TYPE <= size && ((*typesOfMsg)[request->TYPE]->empty()
			|| checkBuffer((*typesOfMsg)[request->TYPE], request->TIME, limit))) {
			(*typesOfMsg)[request->TYPE]->push_back(request);
		}
		request = new Sdata();
	} while (request->readData(fileIn));
	delete[] request->MSG;
	delete request;

	fileIn->close();
	delete fileIn;

	return true;
}

//Computed mean number of messages of all seconds for each request type
void meanOfEachMsg(std::ofstream * const fileOut, map * const typesOfMsg, const int32 size) {

	int32 sec = 0;
	double mean = 0;
	int time = -1;

	for (int32 i = 0; i < size; i++) {
		if (typesOfMsg->find(i) != typesOfMsg->end()) {
			for (vector::iterator it = (*typesOfMsg)[i]->begin(); it != (*typesOfMsg)[i]->end(); ++it) {
				if (static_cast<int>((*it)->TIME) > time) {
					time = (*it)->TIME;
					sec++;
				}
			}
			fileOut->write(reinterpret_cast<char*>(&i), sizeof(int32));
			mean = static_cast<double>((*typesOfMsg)[i]->size()) / sec;
			fileOut->write(reinterpret_cast<char*>(&mean), sizeof(double));
			time = -1;
			sec = 0;
		}
	}

	fileOut->close();
	delete fileOut;
}

void functionsShell(std::ifstream * const fileIn, std::ofstream * const fileOut) {
	const int32 size = 100000;
	const int32 limit = 2048;
	map *typesOfMsg = new map();
	if (!handlerOfData(fileIn, typesOfMsg, size, limit)) {
		fileOut->close();
		delete fileOut;
		return;
	}

	meanOfEachMsg(fileOut, typesOfMsg, size);

	for (int32 i = 0; i < typesOfMsg->size(); i++) {
		if (typesOfMsg->find(i) != typesOfMsg->end()) {
			for (int32 j = 0; j < (*typesOfMsg)[i]->size(); j++) {
				delete[] (*typesOfMsg)[i]->at(j)->MSG;
				delete (*typesOfMsg)[i]->at(j);
			}
			delete (*typesOfMsg)[i];
		}
	}

	delete typesOfMsg;
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
			std::cout << "Error path for " << nameOut + number + format	<< std::endl;
			fileIn->close();
			fileOut->close();
			delete fileIn;
			delete fileOut;
			continue;
		}
		threads.create_thread(boost::bind(&functionsShell, fileIn, fileOut));
	}

	threads.join_all();

	return 0;
}

