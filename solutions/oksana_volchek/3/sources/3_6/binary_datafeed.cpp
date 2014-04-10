#include <fstream>
#include <iostream>
#include <map>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
//#include <boost/timer/timer.hpp>
#include "stock_data.h"

using namespace std;

namespace threadManagement
{
	boost::mutex myMutex;
	static const size_t threadsCount = 4;
}

typedef map<const string, ofstream*> ofstreamInfo;

void writeSortMsg(ifstream & myFilein, ofstreamInfo & myStockNameMap){
	boost::mutex::scoped_lock lock(threadManagement::myMutex);
	while (!myFilein.eof()){
		binary_reader::stock_data *info = new binary_reader::stock_data(myFilein);
		if (myFilein.good()){
			try {
				const string nameFileout = BINARY_DIR "/output_" + boost::lexical_cast<string>(info->get_stockName()) + ".txt";
				if (!myStockNameMap[nameFileout]){
					ofstream* thisFileout = new ofstream(nameFileout, ios::binary);
					myStockNameMap[nameFileout] = thisFileout;
				}
				
				info->write(*myStockNameMap[nameFileout]);
				delete info;
			}
			catch (...){
				cerr << "Unable to employ lexical_cast!" << endl;
			}
		}
	}
}

int main()
{
	ifstream filein;
	filein.open(BINARY_DIR "/input.txt", ios::binary);
	if(!filein.is_open()){
		cerr << "Unable to open file input.txt!" << endl;
		return 1;
	}

	ofstreamInfo stockNamesAttested;
	boost::thread_group myThreads;
	// boost::timer::auto_cpu_timer t;

	for (size_t i = 0; i < threadManagement::threadsCount; ++i){
        myThreads.create_thread(boost::bind(&writeSortMsg, boost::ref(filein), boost::ref(stockNamesAttested)));
	}

	myThreads.join_all();
	filein.close();
	
	for (ofstreamInfo::iterator iter = stockNamesAttested.begin(); iter != stockNamesAttested.end(); ++iter){
		(iter->second)->close();
	}

	return 0;
}
