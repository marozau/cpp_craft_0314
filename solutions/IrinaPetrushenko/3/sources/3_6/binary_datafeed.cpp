#include <stock_data.h>

#include <iostream>
#include <fstream>
#include <map>
#include <queue>

#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/lexical_cast.hpp>

using namespace binary_reader;
using namespace std;

namespace task_3_3{
	static boost::mutex mtx_el;
	static boost::mutex mtx_out;
	static size_t it_for_queue = 0;

	void local_write_void_for_stock_data (boost::shared_ptr<stock_data>  mm, boost::shared_ptr<ofstream> out){
			mm->write_stock_name(*out);
			mm->write_data(*out);
			mm->write_price(*out);
			mm->write_volume(*out);
			mm->write_f2(*out);
	}

	void almost_main (ifstream * const inn, map <string, boost::shared_ptr<ofstream> > * const map_of_stock_names, vector <boost::shared_ptr<stock_data> > * const qu_el){

		boost::shared_ptr<ofstream> out;
		string ss;
		while (!inn->eof()){
					
					{
						boost::mutex::scoped_lock lock(task_3_3::mtx_el);
						qu_el->push_back (boost::shared_ptr<stock_data> (new stock_data (*inn)));						
					}
						if (inn->eof()) 
							break;
					{	
						boost::mutex::scoped_lock lock_out(task_3_3::mtx_out);
						{
							boost::mutex::scoped_lock lock(task_3_3::mtx_el);
							ss=static_cast<string>((*qu_el)[it_for_queue]->stock_name());						
						}

						if (map_of_stock_names->count(ss)==0){
								const string index="/output_"+ss+".txt";
								const string out_name = BINARY_DIR+index;
								{
									boost::shared_ptr<ofstream> temp (new ofstream (out_name.c_str(),std::ios::binary));
									out = temp;
									map_of_stock_names->insert(make_pair(ss,out));
								}
						}
						else
								out = (map_of_stock_names->find(ss))->second;
										
						{
							boost::mutex::scoped_lock lock(task_3_3::mtx_el);
							task_3_3::local_write_void_for_stock_data ((*qu_el)[it_for_queue], out);	
						}

						it_for_queue++;
					}
					
			}
			
	}

}
int main()
{
		
	    ifstream inn (BINARY_DIR "/input.txt",std::ios::binary);

		if (inn.is_open()){

			boost::thread_group group_of_threads;
			map <string, boost::shared_ptr<ofstream> > map_of_stock_names;
			vector <boost::shared_ptr<stock_data> > qu_el;

			static const size_t threads_count = 4;

			for (size_t i =0; i<threads_count;i++){
				group_of_threads.create_thread (boost::bind(& task_3_3::almost_main, & inn, & map_of_stock_names, & qu_el));
			}
			group_of_threads.join_all();

			for (map<string, boost::shared_ptr<ofstream>>::iterator i = map_of_stock_names.begin();i!=map_of_stock_names.end();i++)
				i->second->close();
			
		}
		else{
			return 1;
		}
		
		inn.close();
}

