#include <iostream>
#include <fstream>
#include <boost/cstdint.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

typedef boost::uint32_t uint_32;
typedef boost::gregorian::date date;

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

	bool readData(std::fstream &fileIn, const uint_32 sizeStr);
	bool writeData(std::fstream &fileOut, uint_32 days, const uint_32 sizeStr) const;
};

bool Sdata::readData(std::fstream &fileIn, const uint_32 sizeStr)
{
	fileIn.read(reinterpret_cast<char*>(stock_name), (sizeStr - 1) * sizeof(char));
	stock_name[sizeStr - 1] = '\0';
	fileIn.read(reinterpret_cast<char*>(date_time), (sizeStr - 1) * sizeof(char));
	date_time[sizeStr - 1] = '\0';
	fileIn.read(reinterpret_cast<char*>(&price), sizeof(double));
	fileIn.read(reinterpret_cast<char*>(&vwap), sizeof(double));
	fileIn.read(reinterpret_cast<char*>(&volume), sizeof(uint_32));
	fileIn.read(reinterpret_cast<char*>(&f1), sizeof(double));
	fileIn.read(reinterpret_cast<char*>(&t1), sizeof(double));
	fileIn.read(reinterpret_cast<char*>(&f2), sizeof(double));
	fileIn.read(reinterpret_cast<char*>(&f3), sizeof(double));
	fileIn.read(reinterpret_cast<char*>(&f4), sizeof(double));
	if(!fileIn)return false;
	return true;
}

bool Sdata::writeData(std::fstream &fileOut, uint_32 days, const uint_32 sizeStr) const
{
	fileOut.write(reinterpret_cast<const char*>(stock_name), sizeStr * sizeof(char));
	fileOut.write(reinterpret_cast<const char*>(&days), sizeof(uint_32));
	fileOut.write(reinterpret_cast<const char*>(&vwap), sizeof(double));
	fileOut.write(reinterpret_cast<const char*>(&volume), sizeof(uint_32));
	fileOut.write(reinterpret_cast<const char*>(&f2), sizeof(double));
	if(!fileOut)return false;
	return true;
}

//Parsed request to get necessary information
void parseInputData(std::fstream &fileIn, std::fstream &fileOut, const uint_32 sizeStr)
{

	Sdata *request = new Sdata();

	if(!request->readData(fileIn, sizeStr))
	{
		std::cout << "There is no data in input file" << std::endl;
		fileIn.close();
		fileOut.close();
		exit(1);
	}

	const uint_32 daysOfYear = 372;
	const uint_32 daysOfMonth = 31;
	uint_32 days = 0;
	date *dateShell = NULL;

	do
	{
		dateShell = new date(boost::gregorian::from_undelimited_string(request->date_time));
		days = dateShell->year() * daysOfYear + (dateShell->month()-1) * daysOfMonth + dateShell->day();

		if(!request->writeData(fileOut, days, sizeStr))
		{
			std::cout << "Write error" << std::endl;
			fileIn.close();
			fileOut.close();
			exit(1);
		}

		delete request;
		request = new Sdata();
		delete dateShell;
	} while (request->readData(fileIn, sizeStr));
	delete request;
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

	std::fstream fileOut;
	fileOut.open( BINARY_DIR "/output.txt", std::ios::binary | std::ios::out);
	if (!fileOut)
	{
		std::cout << "Error path for output.txt" << std::endl;
		fileIn.close();
		fileOut.close();
		exit(1);
	}

	const uint_32 sizeStr = 9;
	parseInputData(fileIn, fileOut, sizeStr);

	fileIn.close();
	fileOut.close();

	return 0;
}

