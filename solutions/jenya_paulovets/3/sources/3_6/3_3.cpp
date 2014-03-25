#include <iostream>
#include <fstream>
#include <boost/cstdint.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>

typedef boost::uint32_t int32;
typedef boost::gregorian::date date;

struct Sdata {
	char stock_name[9];
	char date_time[9];
	double price;
	double vwap;
	int32 volume;
	double f1;
	double t1;
	double f2;
	double f3;
	double f4;

	Sdata() :
			price(0), vwap(0), volume(0), f1(0), t1(0), f2(0), f3(0), f4(0) {
	}

	bool readData(std::ifstream * const fileIn, const int32 sizeStr);
	bool writeData(std::ofstream * const fileOut, int32 days, const int32 sizeStr);
};

bool Sdata::readData(std::ifstream * const fileIn, const int32 sizeStr) {
	fileIn->read(reinterpret_cast<char*>(stock_name), (sizeStr - 1) * sizeof(char));
	stock_name[sizeStr] = '\0';
	fileIn->read(reinterpret_cast<char*>(date_time), (sizeStr - 1) * sizeof(char));
	date_time[sizeStr] = '\0';
	fileIn->read(reinterpret_cast<char*>(&price), sizeof(double));
	fileIn->read(reinterpret_cast<char*>(&vwap), sizeof(double));
	fileIn->read(reinterpret_cast<char*>(&volume), sizeof(int32));
	fileIn->read(reinterpret_cast<char*>(&f1), sizeof(double));
	fileIn->read(reinterpret_cast<char*>(&t1), sizeof(double));
	fileIn->read(reinterpret_cast<char*>(&f2), sizeof(double));
	fileIn->read(reinterpret_cast<char*>(&f3), sizeof(double));
	fileIn->read(reinterpret_cast<char*>(&f4), sizeof(double));
	if (!*fileIn)
		return false;
	return true;
}

bool Sdata::writeData(std::ofstream * const fileOut, int32 days, const int32 sizeStr) {
	fileOut->write(reinterpret_cast<char*>(stock_name), (sizeStr - 1) * sizeof(char));
	fileOut->write(reinterpret_cast<char*>(&days), sizeof(int32));
	fileOut->write(reinterpret_cast<char*>(&vwap), sizeof(double));
	fileOut->write(reinterpret_cast<char*>(&volume), sizeof(int32));
	fileOut->write(reinterpret_cast<char*>(&f2), sizeof(double));
	if (!*fileOut)
		return false;
	return true;
}

//Parsed request to get necessary information
void parseInputData(std::ifstream * const fileIn, std::ofstream * const fileOut) {
	Sdata *request = new Sdata();

	const int32 sizeStr = 9;

	if (!request->readData(fileIn, sizeStr)) {
		std::cout << "There is no data in input file" << std::endl;
		fileIn->close();
		fileOut->close();
		delete fileIn;
		delete fileOut;
		return;
	}

	const int32 daysOfYear = 372;
	const int32 daysOfMonth = 31;
	int32 days = 0;
	date *dateShell = NULL;

	do {
		dateShell = new date(boost::gregorian::from_undelimited_string(request->date_time));
		days = dateShell->year() * daysOfYear + (dateShell->month() - 1) * daysOfMonth + dateShell->day();

		if (!request->writeData(fileOut, days, sizeStr)) {
			std::cout << "Write error" << std::endl;
			fileIn->close();
			fileOut->close();
			delete fileIn;
			delete fileOut;
			return;
		}

		delete request;
		request = new Sdata();
		delete dateShell;
	} while (request->readData(fileIn, sizeStr));
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
		threads.create_thread(boost::bind(&parseInputData, fileIn, fileOut));
	}

	threads.join_all();

	return 0;
}

