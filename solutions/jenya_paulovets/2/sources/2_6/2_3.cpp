#include <iostream>
#include <fstream>
#include <boost/cstdint.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

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
};

//Parsed request to get necessary information
void parseInputData(std::fstream &fileIn, std::fstream &fileOut, const int32 sizeStr) {

	Sdata *request = new Sdata();

	fileIn.read(reinterpret_cast<char*>(request->stock_name), (sizeStr - 1) * sizeof(char));
	if (!fileIn) {
		std::cout << "There is no data in input file" << std::endl;
		fileIn.close();
		fileOut.close();
		exit(1);
	}
	fileIn.read(reinterpret_cast<char*>(request->date_time), (sizeStr - 1) * sizeof(char));
	fileIn.read(reinterpret_cast<char*>(&request->price), sizeof(double));
	fileIn.read(reinterpret_cast<char*>(&request->vwap), sizeof(double));
	fileIn.read(reinterpret_cast<char*>(&request->volume), sizeof(int32));
	fileIn.read(reinterpret_cast<char*>(&request->f1), sizeof(double));
	fileIn.read(reinterpret_cast<char*>(&request->t1), sizeof(double));
	fileIn.read(reinterpret_cast<char*>(&request->f2), sizeof(double));
	fileIn.read(reinterpret_cast<char*>(&request->f3), sizeof(double));
	fileIn.read(reinterpret_cast<char*>(&request->f4), sizeof(double));

	int32 daysOfYear = 372;
	int32 daysOfMonth = 31;
	int32 days = 0;
	date *dateShell = NULL;

	do {
		dateShell = new date(boost::gregorian::from_undelimited_string(request->date_time));
		days = dateShell->year() * daysOfYear + (dateShell->month()-1) * daysOfMonth + dateShell->day();

		fileOut.write(reinterpret_cast<char*>(request->stock_name), sizeStr * sizeof(char));
		if (!fileOut) {
			std::cout << "Write error" << std::endl;
			fileIn.close();
			fileOut.close();
			exit(1);
		}
		fileOut.write(reinterpret_cast<char*>(&days), sizeof(int32));
		fileOut.write(reinterpret_cast<char*>(&request->vwap), sizeof(double));
		fileOut.write(reinterpret_cast<char*>(&request->volume), sizeof(int32));
		fileOut.write(reinterpret_cast<char*>(&request->f2), sizeof(double));

		delete request;
		request = new Sdata();
		fileIn.read(reinterpret_cast<char*>(request->stock_name), (sizeStr - 1) * sizeof(char));
		fileIn.read(reinterpret_cast<char*>(request->date_time), (sizeStr - 1) * sizeof(char));
		fileIn.read(reinterpret_cast<char*>(&request->price), sizeof(double));
		fileIn.read(reinterpret_cast<char*>(&request->vwap), sizeof(double));
		fileIn.read(reinterpret_cast<char*>(&request->volume), sizeof(int32));
		fileIn.read(reinterpret_cast<char*>(&request->f1), sizeof(double));
		fileIn.read(reinterpret_cast<char*>(&request->t1), sizeof(double));
		fileIn.read(reinterpret_cast<char*>(&request->f2), sizeof(double));
		fileIn.read(reinterpret_cast<char*>(&request->f3), sizeof(double));
		fileIn.read(reinterpret_cast<char*>(&request->f4), sizeof(double));
		delete dateShell;
	} while (fileIn);
	delete request;
}

//Console check for result data
void concoleCheckForOutput(std::fstream &fileIn, const int32 sizeStr){
	char *stock_name=NULL;
	int32 volume=0;
	int32 days=0;
	double vwap=0;
	double f2=0;
	stock_name=new char[sizeStr];

	fileIn.read(reinterpret_cast<char*>(stock_name), sizeStr * sizeof(char));
	if (!fileIn) {
		std::cout << "There is no data in output file" << std::endl;
		fileIn.close();
		exit(1);
	}
	fileIn.read(reinterpret_cast<char*>(&days), sizeof(int32));
	fileIn.read(reinterpret_cast<char*>(&vwap), sizeof(double));
	fileIn.read(reinterpret_cast<char*>(&volume), sizeof(int32));
	fileIn.read(reinterpret_cast<char*>(&f2), sizeof(double));


	do {
	    std::cout<<stock_name<<" "<<days<<" "<<vwap<<" "<<volume<<" "<<f2<<std::endl;

	    delete []stock_name;
	    stock_name=new char[sizeStr];
	    fileIn.read(reinterpret_cast<char*>(stock_name), sizeStr * sizeof(char));
	    fileIn.read(reinterpret_cast<char*>(&days), sizeof(int32));
	    fileIn.read(reinterpret_cast<char*>(&vwap), sizeof(double));
	    fileIn.read(reinterpret_cast<char*>(&volume), sizeof(int32));
	    fileIn.read(reinterpret_cast<char*>(&f2), sizeof(double));
	} while (fileIn);
	delete []stock_name;
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

	const int32 sizeStr = 9;
	parseInputData(fileIn, fileOut, sizeStr);

	fileIn.close();
	fileOut.close();

	fileIn.open( BINARY_DIR "/output.txt", std::ios::binary | std::ios::in);
			if (!fileIn) {
				std::cout << "Error path for output.txt" << std::endl;
				fileIn.close();
				exit(1);
			}

	concoleCheckForOutput(fileIn, sizeStr);

	fileIn.close();

	return 0;
}

