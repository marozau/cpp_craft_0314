#include <fstream>
#include <iostream>
#include <map>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
//#include <boost/timer/timer.hpp>
#include "stock_data.h"

using namespace std;

namespace threadManagement
{
	boost::mutex myMutex;
	static const size_t threadsCount = 10;
}

void writeMsg(ofstream* fileout, binary_reader::stock_data* currentMsg){
	boost::mutex::scoped_lock lock(threadManagement::myMutex);
	currentMsg->write(*fileout);
	delete currentMsg;
}

int main()
{
	ifstream filein;
	filein.open(BINARY_DIR "/input.txt", ios::binary);
	if(!filein.is_open()){
		cerr << "Unable to open file input.txt!" << endl;
		return 1;
	}

	map<const string, ofstream*> stockNamesAttested;
	boost::asio::io_service myService;
	boost::asio::io_service::work myWork(myService);
	boost::thread_group myThreads;
	for (size_t i = 0; i < threadManagement::threadsCount; ++i){
	    myThreads.create_thread(boost::bind(&boost::asio::io_service::run, &myService));
	}

	// boost::timer::auto_cpu_timer t;

	while (!filein.eof()){
		binary_reader::stock_data *info = new binary_reader::stock_data(filein);
		if (filein.good()){
			try {
				const string nameFileout = BINARY_DIR "/output_" + boost::lexical_cast<string>(info->get_stockName()) + ".txt";
				if (!stockNamesAttested[nameFileout]){
					ofstream* thisFileout = new ofstream(nameFileout, ios::binary);
					stockNamesAttested[nameFileout] = thisFileout;
				}
				myService.post(boost::bind(&writeMsg, stockNamesAttested[nameFileout], info));
			}
			catch (...){
				cerr << "Unable to employ lexical_cast!" << endl;
			}
		}
	}
	myService.stop();
	myThreads.join_all();
	filein.close();
	for (map<const string, ofstream*>::iterator iter = stockNamesAttested.begin(); iter != stockNamesAttested.end(); ++iter){
		(iter->second)->close();
	}
	return 0;
}
