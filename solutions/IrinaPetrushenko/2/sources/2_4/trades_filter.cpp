#include <market_message.h>
#include <iostream>
#include <fstream>
#include <boost/cstdint.hpp>

using namespace binary_reader;
using namespace std;

namespace task4{
	static const size_t type_min = 1u;
	static const size_t type_max = 4u;
	static const size_t diff = 2;
}
bool is_good_type (const size_t t){
	return (t>=task4::type_min && t<=task4::type_max) ;
} 

int main()
{
	ifstream inn (BINARY_DIR "/input.txt" , std::ios::binary);
	ofstream out (BINARY_DIR "/output.txt", std::ios::binary);
	
	if (inn.is_open()){

		size_t cur_time=task4::diff;
		
		while (!inn.eof()){
			market_message m(inn);
			if (inn.eof()) break;
			if (is_good_type(m.type()) && m.time()>cur_time-task4::diff)		m.write(out);
			if (m.time()>cur_time) cur_time=m.time();
		}
		

	}
	else{
		cerr<<"Input file was not opened"<<endl;
		return 1;
	}
	inn.close();
	out.close();
}

