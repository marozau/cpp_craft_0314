#include <iostream>
#include <fstream>
#include <string.h>
#include <boost/cstdint.hpp>
#include <vector>
#include <map>

typedef boost::uint32_t uint_32;

struct Sdata {
	uint_32 type;
	uint_32 time;
	uint_32 len;
	char *msg;

	Sdata():type(0), time(0), len(0), msg(NULL)
	{}

	bool readData(std::fstream &fileIn);
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

typedef std::vector<Sdata*> vector;
typedef std::map<const uint_32, vector*> map;

//Check buffer limit
bool checkBuffer(map &typesOfMsg, const Sdata *const request, const uint_32 limit)
{
	uint_32 count = 0;
	uint_32 sumLenStr = 0;
	vector *vect = typesOfMsg[request->type];
	const uint_32 time = request->time;

	for (vector::iterator it = vect->begin(); it != vect->end(); ++it)
	{
		if ((*it)->time == time)
		{
			count++;
			sumLenStr += (*it)->len + 1;
		}
	}

	if ((count+1) * 3  * sizeof(uint_32) + sumLenStr + request->len + 1 > limit)
		return false;
	else
		return true;
}

//Created associative array for storage of vectors, which contain requests of each type
void handlerOfData(std::fstream &fileIn, map &typesOfMsg, const uint_32 size, const uint_32 limit)
{

	Sdata *request = new Sdata();

	if(!request->readData(fileIn))
	{
			std::cout << "There is no data in input file" << std::endl;
			fileIn.close();
			exit(1);
	}

	uint_32 sizeOfReq = 0;

	do {
		sizeOfReq = 3 * sizeof(uint_32) + request->len + 1;

		if (request->type <= size && sizeOfReq <= limit && typesOfMsg.find(request->type) == typesOfMsg.end())
			typesOfMsg[request->type] = new vector;
		if (request->type <= size && sizeOfReq <= limit && (typesOfMsg[request->type]->empty()
			|| checkBuffer(typesOfMsg, request, limit)))
		{
			typesOfMsg[request->type]->push_back(request);
		}
		request = new Sdata();
	} while (request->readData(fileIn));
	delete[] request->msg;
	delete request;
}

//Computed mean number of messages of all seconds for each request type
void meanOfEachMsg(std::fstream &fileOut, map &typesOfMsg, const uint_32 size)
{

	uint_32 sec = 0;
	double mean = 0;
	int time = -1;

	for (uint_32 i = 0; i < size; i++)
	{
		if (typesOfMsg.find(i) != typesOfMsg.end())
		{
			for (vector::iterator it = typesOfMsg[i]->begin(); it != typesOfMsg[i]->end(); ++it)
			{
				if (static_cast<int>((*it)->time) > time)
				{
					time = (*it)->time;
					sec++;
				}
			}
			fileOut.write(reinterpret_cast<const char*>(&i), sizeof(uint_32));
			mean = static_cast<double>(typesOfMsg[i]->size()) / sec;
			fileOut.write(reinterpret_cast<const char*>(&mean), sizeof(double));
			time = -1;
			sec = 0;
		}
	}
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

	const uint_32 size = 100000;
	const uint_32 limit = 2048;
	map typesOfMsg;
	handlerOfData(fileIn, typesOfMsg, size, limit);
	fileIn.close();

	std::fstream fileOut;
	fileOut.open( BINARY_DIR "/output.txt", std::ios::binary | std::ios::out);
	if (!fileOut)
	{
		std::cout << "Error path for output.txt" << std::endl;
		fileIn.close();
		fileOut.close();
		exit(1);
	}

	meanOfEachMsg(fileOut, typesOfMsg, size);
	fileOut.close();

	for (uint_32 i = 0; i < typesOfMsg.size(); i++)
	{
		if (typesOfMsg.find(i) != typesOfMsg.end())
		{
			for (uint_32 j = 0; j < typesOfMsg[i]->size(); j++)
			{
				delete[] typesOfMsg[i]->at(j)->msg;
				delete typesOfMsg[i]->at(j);
			}
			delete typesOfMsg[i];
		}
	}

	return 0;
}

