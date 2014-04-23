#include <iostream>
#include <fstream>
#include <boost/cstdint.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/thread.hpp>
#include <map>

class fileOut;

typedef boost::uint32_t uint_32;
typedef boost::gregorian::date date;
typedef boost::mutex io_mutex;
typedef std::map<const std::string, fileOut*> map;

struct Sdata {
	char stock_name[9];
	char date_time[9];
	double price;
	double vwap;
	uint_32 volume;
	double f1;
	double t1;
	double f2;
	double f3;
	double f4;

	Sdata() : price(0), vwap(0), volume(0), f1(0), t1(0), f2(0), f3(0), f4(0)
	{}

	bool readData(std::ifstream * const fileIn, const uint_32 sizeStr);
	bool writeData(std::ofstream * const fileOut, uint_32 days, const uint_32 sizeStr) const;
};

bool Sdata::readData(std::ifstream * const fileIn, const uint_32 sizeStr)
{
	fileIn->read(reinterpret_cast<char*>(stock_name), (sizeStr - 1) * sizeof(char));
	if( fileIn->eof() ) return false;
	stock_name[sizeStr] = '\0';
	fileIn->read(reinterpret_cast<char*>(date_time), (sizeStr - 1) * sizeof(char));
	date_time[sizeStr] = '\0';
	fileIn->read(reinterpret_cast<char*>(&price), sizeof(double));
	fileIn->read(reinterpret_cast<char*>(&vwap), sizeof(double));
	fileIn->read(reinterpret_cast<char*>(&volume), sizeof(uint_32));
	fileIn->read(reinterpret_cast<char*>(&f1), sizeof(double));
	fileIn->read(reinterpret_cast<char*>(&t1), sizeof(double));
	fileIn->read(reinterpret_cast<char*>(&f2), sizeof(double));
	fileIn->read(reinterpret_cast<char*>(&f3), sizeof(double));
	fileIn->read(reinterpret_cast<char*>(&f4), sizeof(double));
	if (!*fileIn)
		return false;
	return true;
}

bool Sdata::writeData(std::ofstream * const fileOut, uint_32 days, const uint_32 sizeStr) const
{
	fileOut->write(reinterpret_cast<const char*>(stock_name), sizeStr * sizeof(char));
	fileOut->write(reinterpret_cast<const char*>(&days), sizeof(uint_32));
	fileOut->write(reinterpret_cast<const char*>(&vwap), sizeof(double));
	fileOut->write(reinterpret_cast<const char*>(&volume), sizeof(uint_32));
	fileOut->write(reinterpret_cast<const char*>(&f2), sizeof(double));
	if (!*fileOut)
		return false;
	return true;
}

class fileOut
{
	io_mutex mutex;
	std::ofstream *out;
public:
	fileOut(const char * const name);
	void parseInputData(const Sdata * const req);
	~fileOut();
};

fileOut::fileOut(const char * const name) {
	const std::string ext = ".txt";
	const std::string typeOfFile = "output_";
	const std::string fName = std::string(BINARY_DIR).append("/").append(typeOfFile).append(name).append(ext);

	out = new std::ofstream(fName.c_str(), std::ios::binary);
}

//Parsed request to get necessary information
void fileOut::parseInputData(const Sdata * const request)
{
	const uint_32 sizeStr = 9;

	const uint_32 daysOfYear = 372;
	const uint_32 daysOfMonth = 31;
	date *dateShell = NULL;

	dateShell = new date(boost::gregorian::from_undelimited_string(request->date_time));
	const uint_32 days = (dateShell->year() - 1) * daysOfYear + (dateShell->month() - 1) * daysOfMonth + dateShell->day();

	{
		boost::mutex::scoped_lock lock(mutex);

		if (!request->writeData(out, days, sizeStr))
		{
			std::cout << "Write error" << std::endl;
		}
	}

	delete request;
}

fileOut::~fileOut()
{
	out->close();
	delete out;
}

int main(int argc, char **argv)
{
	std::ifstream *fileIn = new std::ifstream( BINARY_DIR "/input.txt", std::ios::binary);
	if (!*fileIn)
	{
		std::cout << "There is no input file" << std::endl;
		delete fileIn;
		return 1;
	}

	map *outFiles = new map();
	boost::thread_group threads;
	const uint_32 sizeStr = 9;

	do {
		Sdata *request = new Sdata();

		if (!request->readData(fileIn, sizeStr))
		{
			std::cout << "There is no more data" << std::endl;
			fileIn->close();
			delete request;
			delete fileIn;
			break;
		}

		if (outFiles->find(request->stock_name) == outFiles->end())
			(*outFiles)[request->stock_name] = new fileOut(request->stock_name);

		threads.create_thread(boost::bind(&fileOut::parseInputData, (*outFiles)[request->stock_name], request));
	} while (*fileIn);

	threads.join_all();

	for (map::iterator it = outFiles->begin(); it != outFiles->end(); ++it)
	{
		delete it->second;
	}

	delete outFiles;

	return 0;
}

