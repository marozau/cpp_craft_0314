#include <market_message.h>
#include <iostream>
#include <fstream>
#include <boost/cstdint.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/lexical_cast.hpp>

using namespace binary_reader;
using namespace std;

namespace task4{
	static const boost::uint32_t type_min = 1u;
	static const boost::uint32_t type_max = 4u;
	static const boost::uint32_t diff = 2;
	static const boost::uint32_t dtest = 3;
}
bool is_good_type (const boost::uint32_t t){
	return (t>=task4::type_min && t<=task4::type_max) ;
} 


void main_func (const boost::uint32_t i){
		
		std::stringstream sss;
		sss.width(3);
		sss<<std::setfill('0');
		sss<<i;
		string format;
		sss>>format;

		string index="/input";
		const string inn_name =BINARY_DIR+index+"_"+format+".txt";

		ifstream inn (inn_name.c_str(), std::ios::binary);

		if (inn.is_open()){
			index="/output";
			const string out_name = BINARY_DIR+index+"_"+format+".txt";

			ofstream out (out_name.c_str(), std::ios::binary);

			boost::uint32_t cur_time = 0;
			while (!inn.eof()){
				market_message m(inn);
				if (inn.eof()) 
					break;
				if (is_good_type(m.type()) && (m.time()+task4::diff>cur_time) )		
					m.write(out);
				if (m.time()>cur_time) 
					cur_time=m.time();
			}
			out.close();
		}
		else{
			return;
		}
		inn.close();
}

int main()
{
	boost::thread_group th_tests;
	static const boost::uint32_t threads_amount = 1000;
	for( boost::uint32_t i = 1; i < threads_amount; ++i ){
		th_tests.create_thread ( boost::bind(&main_func,  i) );
	}
	th_tests.join_all();
}

