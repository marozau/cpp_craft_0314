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




int main()
{
		ifstream inn (BINARY_DIR "/input.txt",std::ios::binary);

		if (inn.is_open()){

			map <string, ofstream *> map_of_stock_names;
			while (!inn.eof()){

				stock_data m(inn);
				if (inn.eof()) 
					break;
				string ss=static_cast<string>(m.stock_name());

				if (map_of_stock_names.count(ss)==0){

					string index="/output_"+ss+".txt";
					string out_name = BINARY_DIR+index;
					ofstream * out =new ofstream (out_name.c_str(),std::ios::binary);
					
					map_of_stock_names.insert(make_pair(ss,out));

					m.write_stock_name(*out);
					m.write_data(*out);
					m.write_price(*out);
					m.write_volume(*out);
					m.write_f2(*out);
				}
				else{
					ofstream * out = (map_of_stock_names.find(ss))->second;
					m.write_stock_name(*out);
					m.write_data(*out);
					m.write_price(*out);
					m.write_volume(*out);
					m.write_f2(*out);
				}
			}

		}
		else{
			cerr<<"Input file was not opened"<<endl;
			return 1;
		}
		inn.close();
}

