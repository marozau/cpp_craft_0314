#include <stock_data.h>
#include <iostream>
#include <fstream>

#include <boost/cstdint.hpp>

using namespace binary_reader;
using namespace std;


int main()
{
	ifstream inn (BINARY_DIR "/input.txt" , std::ios::binary);
	ofstream out (BINARY_DIR "/output.txt", std::ios::binary);

	if (inn.is_open()){
		while (!inn.eof()){
			stock_data m(inn);
			if (inn.eof()) 
				break;
			m.write_stock_name(out);
			m.write_data(out);
			m.write_price(out);
			m.write_volume(out);
			m.write_f2(out);
		}

	}
	else{
		cerr<<"Input file was not opened"<<endl;
		return 1;
	}
	inn.close();
	out.close();
}

