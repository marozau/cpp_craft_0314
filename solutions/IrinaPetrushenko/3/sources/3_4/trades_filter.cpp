#include <market_message.h>
#include <iostream>
#include <fstream>
#include <boost/cstdint.hpp>
#include <stdlib.h>

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/lexical_cast.hpp>

using namespace binary_reader;
using namespace std;

namespace task4{
	static const size_t type_min = 1u;
	static const size_t type_max = 4u;
	static const boost::uint32_t diff = 2;
	static const size_t dtest = 3;
}
bool is_good_type (const size_t t){
	return (t>=task4::type_min && t<=task4::type_max) ;
} 


void main_func (size_t i){
		string index = boost::lexical_cast<std::string>(i);
		string format ="000";

		format.insert(format.size() - index.size(), index);
		format.erase(format.begin()+task4::dtest,format.end());
		index="/input";
		string inn_name =BINARY_DIR+index+"_"+format+".txt";
		index="/output";
		string out_name = BINARY_DIR+index+"_"+format+".txt";

		ifstream inn (inn_name.c_str(), std::ios::binary);
		ofstream out (out_name.c_str(), std::ios::binary);

		if (inn.is_open()){
			boost::uint32_t cur_time=task4::diff;
		
			while (!inn.eof()){
				market_message m(inn);
				if (inn.eof()) break;
				if (is_good_type(m.type()) && m.time()>cur_time-task4::diff)		m.write(out);
				if (m.time()>cur_time) cur_time=m.time();
			}
		}
		else{
			cerr<<"Input file was not opened"<<endl;
			return;
		}
		inn.close();
		out.close();
}

int main()
{
	boost::thread_group th_tests;
	static const size_t threads_amount = 1000;
	for( size_t i = 1; i < threads_amount; ++i ){
		th_tests.create_thread ( boost::bind(&main_func,  i) );
	}
	th_tests.join_all();
}

