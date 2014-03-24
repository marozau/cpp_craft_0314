#include <market_message.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <boost/cstdint.hpp>

using namespace binary_reader;
using namespace std;

namespace task5{ 
	struct point{
		point(size_t s=0,size_t n=0,size_t t=0):size(s),num(n),time(t),good(false){};
		size_t size;
		size_t num;
		size_t time;
		bool good;
	};
	static const size_t max_size=2048;
}


int main()
{
	ifstream inn (BINARY_DIR "/input.txt" , std::ios::binary);
	ofstream out (BINARY_DIR "/output.txt", std::ios::binary);

	if (inn.is_open()){

		size_t n=0;
		vector <market_message> list;
		size_t types=0;

		while (!inn.eof()){
			market_message m(inn);
			if (inn.eof()) break;
			list.push_back(m);
			if (m.type()>types) types=m.type();
			n++;			
		}

		vector <task5::point>	ans(types+1,task5::point(0,0,0));
		size_t un=0;
		
		for (size_t i=0;i<n;i++){
			if (ans[list[i].type()].size+list[i].size()<=task5::max_size){
				if (ans[list[i].type()].size==0)	ans[list[i].type()].time++;
				ans[list[i].type()].size+=list[i].size();
				ans[list[i].type()].num++;
			}	
			if (i==n-1 || list[i].time()!=list[i+1].time()) {
				for (size_t j=un;j<=i;j++)
					ans[list[j].type()].size=0;
				
				un=i+1;
			}
			ans[list[i].type()].good=true;
		}

		
		for (size_t i=0;i<=types;i++)
			if (ans[i].good){
				if(!out.write(reinterpret_cast<char *>(&i), sizeof(i))) {
					cerr<<"I can not write data"<<endl;
					return 1;
				}
				double temp=0;
				if (ans[i].num!=0) 
					temp = static_cast< double >(ans[i].num)/ans[i].time;
				if(!out.write(reinterpret_cast<char *>(&temp), sizeof(temp))) {
					cerr<<"I can not write data"<<endl;
					return 1;
				}
			}
		

	}
	else{
		cerr<<"Input file was not opened"<<endl;
		return 1;
	}
	inn.close();
	out.close(); 
}

