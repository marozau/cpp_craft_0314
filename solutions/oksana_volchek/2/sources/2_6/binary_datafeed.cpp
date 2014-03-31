#include <fstream>
#include <iostream>
#include <boost/cstdint.hpp>
#include "stock_data.h"

using namespace std;

int main(){
	ifstream filein;
	filein.open(BINARY_DIR "/input.txt", ios::binary);
	if(!filein.is_open()){
		cerr << "Unable to open file input.txt!" << endl;
		return 1;
	}
	
	ofstream fileout;
	fileout.open(BINARY_DIR "/output.txt", ios::binary);

	while (!filein.eof()){
		binary_reader::stock_data info(filein);
		if (filein.good()){
			info.write(fileout);
		}
	}
	fileout.close();
	filein.close();

	return 0;
}