#include <stock_data.h>

#include <iostream>
#include <fstream>
#include <map>

#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/lexical_cast.hpp>

using namespace binary_reader;
using namespace std;

namespace task_3_3{
	static boost::mutex mtx;
	static boost::condition wait_condition;

	void local_write_void_for_stock_data (stock_data * m, ofstream * out){
		{
			boost::mutex::scoped_lock lock(task_3_3::mtx);

			m->write_stock_name(*out);
			m->write_data(*out);
			m->write_price(*out);
			m->write_volume(*out);
			m->write_f2(*out);
			delete m;
		}
	}

	void almost_main (ifstream * inn, map <string, ofstream *> & map_of_stock_names){
			
			stock_data  * m;
			while (!inn->eof()){
				{
					boost::mutex::scoped_lock lock(task_3_3::mtx);
					m = new stock_data (*inn);
				}
			
				if (inn->eof()) 
					break;

				string ss=static_cast<string>(m->stock_name());
				ofstream * out;

				if (map_of_stock_names.count(ss)==0){
					string index="/output_"+ss+".txt";
					string out_name = BINARY_DIR+index;
					{
						boost::mutex::scoped_lock lock(task_3_3::mtx);
						out =new ofstream (out_name.c_str(),std::ios::binary);
						map_of_stock_names.insert(make_pair(ss,out));
					}
				}
				else
					out = (map_of_stock_names.find(ss))->second;

				task_3_3::local_write_void_for_stock_data (m, out);
			}
			
	}

}
int main()
{
		
	    ifstream inn (BINARY_DIR "/input.txt",std::ios::binary);

		if (inn.is_open()){

			boost::thread_group group_of_threads;
			map <string, ofstream *> map_of_stock_names;
			static const size_t threads_count = 4;

			for (size_t i =0; i<threads_count;i++){
				group_of_threads.create_thread (boost::bind(& task_3_3::almost_main, & inn,  map_of_stock_names));
			}
			group_of_threads.join_all();

			for (map<string, ofstream *>::iterator i = map_of_stock_names.begin();i!=map_of_stock_names.end();i++)
				i->second->close();
			
		}
		else{
			cerr<<"Input file was not opened"<<endl;
			return 1;
		}
		
		inn.close();
}

