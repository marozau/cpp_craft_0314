/*
An efficient solution of 3_6 must be O(1) in space,
since we can dispatch messages "on the fly", without
any additional storage, and O(n) in time, since the
number of available threads is constant, e.g. 1, 2
or 4. The proposed single-threaded implementation
satisfies these requirements.

Earlier, I proposed a multi-threaded implementation
with boost::asio. My solution was rejected in favor
of manual thread management. However my revised code
wasn't accepted either: Pavel noted that threads were
now working sequentially, one by one.

I benchmarked all three of my implementations against
the largest test file input_262.txt, 144 MiB in size,
and found just a slight difference in their efficiency. 
Peak memory allocation was ~1.0 MiB with a single
thread, ~1.2 MiB with straightforward multithreading,
and ~2.8 MiB with boost::asio. Execution time of a
release build was ~7 seconds with a single thread,
~8 seconds with straightforward multithreading, and
~6 seconds with boost::asio. I can't conceive of any
obvious speed optimization, since the processing rate
of ~20 MiB/second is not much slower than simply
retrieving binary data from input file.

Following Pavel's advice, I submit a single-threaded
implementation. Hope this will be the final one :)
*/

#include <fstream>
#include <iostream>
#include <map>
#include <boost/lexical_cast.hpp>
#include "stock_data.h"

using namespace std;

typedef map<const string, ofstream*> ofstreamInfo;

int main()
{
	ifstream filein;
	filein.open(BINARY_DIR "/input.txt", ios::binary);
	if(!filein.is_open()){
		cerr << "Unable to open file input.txt!" << endl;
		return 1;
	}

	ofstreamInfo stockNamesAttested;
	while (!filein.eof()){
		binary_reader::stock_data *info = new binary_reader::stock_data(filein);
		if (filein.good()){
			try {
				const string nameFileout = BINARY_DIR "/output_" + boost::lexical_cast<string>(info->get_stockName()) + ".txt";
				if (!stockNamesAttested[nameFileout]){
					ofstream* thisFileout = new ofstream(nameFileout, ios::binary);
					stockNamesAttested[nameFileout] = thisFileout;
				}
				
				info->write(*stockNamesAttested[nameFileout]);
				delete info;
			}
			catch (...){
				cerr << "Unable to employ lexical_cast!" << endl;
			}
		}
	}
	filein.close();
	
	for (ofstreamInfo::iterator iter = stockNamesAttested.begin(); iter != stockNamesAttested.end(); ++iter){
		(iter->second)->close();
	}

	return 0;
}
