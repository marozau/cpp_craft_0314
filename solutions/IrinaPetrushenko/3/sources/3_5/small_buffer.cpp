#include <market_message.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>


#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/lexical_cast.hpp>

using namespace binary_reader;
using namespace std;

namespace task5{ 
	struct point{
		point(boost::uint32_t s=0,size_t n=0,boost::uint32_t t=0):size(s),num(n),time(t),good(false){};
		boost::uint32_t size;
		size_t num;
		boost::uint32_t time;
		bool good;
	};
	static const boost::uint32_t max_size=2048;
	static const size_t dtest = 3;
}


boost::uint32_t size (market_message * l){
	boost::uint32_t len =static_cast<boost::uint32_t> ( strlen(l->msg()));
	return static_cast<boost::uint32_t> (sizeof(l->type())+sizeof(l->time())+sizeof(len)+len);
}


void main_func (size_t i){
		string index = boost::lexical_cast<std::string>(i);
		string format ="000";

		format.insert(format.size() - index.size(), index);
		format.erase(format.begin()+task5::dtest,format.end());
		index="/input";
		string inn_name =BINARY_DIR+index+"_"+format+".txt";
		index="/output";
		string out_name = BINARY_DIR+index+"_"+format+".txt";

		ifstream inn (inn_name.c_str(), std::ios::binary);
		ofstream out (out_name.c_str(), std::ios::binary);
		
		if (inn.is_open()){

			size_t n=0;
			vector <market_message*> list;
			size_t types=0;
			while (!inn.eof()){
				list.push_back(new market_message (inn));
				
				if (inn.eof()) {
					delete list.back();
					list.pop_back();
					break;
				}
				//cerr<<list.back()->type()<<" "<<list.back()->time()<<" "<<list.back()->len()<<" "<<list.back()->msg()<<endl;
				if (list.back()->type()>types) types=list.back()->type();
				n++;			
			}
			vector <task5::point>	ans(types+1,task5::point(0,0,0));
			size_t un=0;
			
			for (size_t i=0;i<n;i++){
				if (ans[list[i]->type()].size+size(list[i])<=task5::max_size){
					if (ans[list[i]->type()].size==0)	ans[list[i]->type()].time++;
					ans[list[i]->type()].size+=size(list[i]);
					ans[list[i]->type()].num++;
				}	
				if (i==n-1 || list[i]->time()!=list[i+1]->time()) {
					for (size_t j=un;j<=i;j++)
						ans[list[j]->type()].size=0;
					
					un=i+1;
				}
				ans[list[i]->type()].good=true;
			}

			
			for (size_t i=0;i<=types;i++)
				if (ans[i].good){
					if(!out.write(reinterpret_cast<char *>(&i), sizeof(i))) {
						cerr<<"I can not write data"<<endl;
						return;
					}
					double temp=0;
					if (ans[i].num!=0) 
						temp = static_cast< double >(ans[i].num)/ans[i].time;

					if(!out.write(reinterpret_cast<char *>(&temp), sizeof(temp))) {
						cerr<<"I can not write data"<<endl;
						return;
					}
				}

			for (size_t i=0;i<n;i++){
				delete list[i];
			}
			list.clear();
			ans.clear();
			

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
		th_tests.create_thread ( boost::bind(&main_func, i) );
	}
	th_tests.join_all();
	
}

