#include <iostream>
#include <fstream>
#include <boost/cstdint.hpp>
#include <boost/thread.hpp>
#include <boost/format.hpp>
#include <vector>
#include <map>

typedef boost::uint32_t uint_32;

struct Sdata {
	uint_32 type;
	uint_32 time;
	uint_32 len;
	char *msg;

	Sdata() : type(0), time(0), len(0), msg(NULL)
	{}

	bool readData(std::ifstream * const fileIn);

	~Sdata()
	{
		delete[] msg;
	}
};

bool Sdata::readData(std::ifstream * const fileIn) {
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

typedef std::vector<Sdata*> vector;
typedef std::map<const uint_32, vector*> map;

//Check buffer limit
bool checkBuffer(map *typesOfMsg, const Sdata * const request, const uint_32 limit)
{
	uint_32 count = 0;
	uint_32 sumLenStr = 0;
	const vector * const vect = (*typesOfMsg)[request->type];
	const uint_32 time = request->time;

	for (vector::const_iterator it = vect->begin(); it != vect->end(); ++it)
	{
		if ((*it)->time == time)
		{
			count++;
			sumLenStr += (*it)->len + 1;
		}
	}

	const uint_32 numOfElem = 3;

	if ((count + 1) * numOfElem * sizeof(uint_32) + sumLenStr + request->len > limit)
		return false;
	else
		return true;
}

//Created associative array for storage of vectors, which contain requests of each type
bool handlerOfData(std::ifstream * const fileIn, map * const typesOfMsg, const uint_32 size, const uint_32 limit)
{
	Sdata *request = new Sdata();

	if (!request->readData(fileIn))
	{
		std::cout << "There is no data in input file" << std::endl;
		fileIn->close();
		delete request;
		delete fileIn;
		return false;
	}

	const uint_32 numOfElem = 3;

	do {
		const uint_32 sizeOfReq = numOfElem * sizeof(uint_32) + request->len;

		if (request->type <= size && sizeOfReq <= limit && typesOfMsg->find(request->type) == typesOfMsg->end())
			(*typesOfMsg)[request->type] = new vector;
		if (request->type <= size && sizeOfReq <= limit && ((*typesOfMsg)[request->type]->empty()
						|| checkBuffer(typesOfMsg, request, limit)))
		{
			(*typesOfMsg)[request->type]->push_back(request);
		}
		else
			delete request;

		request = new Sdata();
	} while (request->readData(fileIn));
	delete request;

	fileIn->close();
	delete fileIn;

	return true;
}

//Computed mean number of messages of all seconds for each request type
void meanOfEachMsg(std::ofstream * const fileOut, map * const typesOfMsg, const uint_32 size) {

	uint_32 sec = 0;
	double mean = 0;
	int time = -1;

	for (uint_32 i = 0; i < size; i++)
	{
		if (typesOfMsg->find(i) != typesOfMsg->end())
		{
			for (vector::const_iterator it = (*typesOfMsg)[i]->begin(); it != (*typesOfMsg)[i]->end(); ++it)
			{
				if (static_cast<int>((*it)->time) > time)
				{
					time = (*it)->time;
					sec++;
				}
			}
			fileOut->write(reinterpret_cast<const char*>(&i), sizeof(uint_32));
			mean = static_cast<double>((*typesOfMsg)[i]->size()) / sec;
			fileOut->write(reinterpret_cast<const char*>(&mean), sizeof(double));
			time = -1;
			sec = 0;
		}
	}

	fileOut->close();
	delete fileOut;
}

void functionsShell(std::ifstream * const fileIn, std::ofstream * const fileOut)
{
	const uint_32 size = 100000;
	const uint_32 limit = 2048;
	map *typesOfMsg = new map();

	if (!handlerOfData(fileIn, typesOfMsg, size, limit))
	{
		fileOut->close();
		delete typesOfMsg;
		delete fileOut;
		return;
	}

	meanOfEachMsg(fileOut, typesOfMsg, size);

	for (uint_32 i = 0; i < typesOfMsg->size(); i++)
	{
		if (typesOfMsg->find(i) != typesOfMsg->end())
		{
			for (uint_32 j = 0; j < (*typesOfMsg)[i]->size(); j++)
			{
				delete (*typesOfMsg)[i]->at(j);
			}
			delete (*typesOfMsg)[i];
		}
	}

	delete typesOfMsg;
}

int main(int argc, char **argv)
{
	boost::thread_group threads;

	const std::string nameIn = "/input_";
	const std::string nameOut = "/output_";
	const std::string format = ".txt";

	for (uint_32 i = 1; i <= 999; i++)
	{
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
		threads.create_thread(boost::bind(&functionsShell, fileIn, fileOut));
	}

	threads.join_all();

	return 0;
}

