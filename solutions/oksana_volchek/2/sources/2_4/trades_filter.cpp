#include <fstream>
#include <iostream>
#include <boost/cstdint.hpp>
#include "market_message.h"

using namespace std;

int main()
{
	ifstream filein;
	filein.open(BINARY_DIR "/input.txt", ios::binary);
	if (!filein.is_open()){
		cout << "Unable to open binary file input.txt!" << endl;
		return 1;
	}

	ofstream fileout;
	boost::uint32_t maxTime = 0;
	fileout.open(BINARY_DIR  "/output.txt", ios::binary);
	while (!filein.eof()){
		try {
			binary_reader::market_message market(filein);
			if (filein.good() && market.type() >= 1 && market.type() <= 4){
				// cout << market.type() << "\t" << market.time() << "\t" << market.len() << "\t" << market.msg() << endl;
				const boost::uint32_t this_time = market.time();
				if (this_time + 2 <= maxTime){
					continue;
				}
				else {
					market.write(fileout);
					if (market.time() > maxTime){
						maxTime = market.time();
					}
				}
			}
		}
		catch (...){
			cerr << "Error!" << endl;
		}
	}
	filein.close();
	fileout.close();

	return 0;
}