
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include "market_message.h"

using namespace std;


int main(int argc, char* argv[]) 
{
	 
	ifstream in( BINARY_DIR "/input.txt", ios:: binary ); 
	if( !in.is_open() )
	{
		cerr<<"Can't open file!"<<endl;
		system("pause");
		return 1;
	} 


	map < boost:: uint32_t, int> sec, kolv;
	map <boost:: uint32_t, boost:: uint32_t> last;
	map < boost::uint32_t, size_t> size;

	try
	{
		binary_reader:: market_message message(in); 
		if (message.check_size(size))
		{
			kolv[message.type()]++;
			size[message.type()]+= message.get_size();
		}
		else 
			kolv[message.type()]=0;

		sec[message.type()]=1;
		last[message.type()] = message.time();
		

		while ( in.good() )
		{
			binary_reader:: market_message message(in); 
			if(!in.good()) break;
			if ( last[message.type()]==message.time() && message.check_size(size) ) 
			{
				size[message.type()]+= message.get_size(); 
				kolv[message.type()]++;
			}
			else 
			{
				if( last[message.type()]!=message.time() )
				{
					sec[message.type()]++;
					kolv[message.type()]++;
					size[message.type()] = 0;
					last[message.type()] = message.time();
				}
				   
				if(!kolv.count( message.type() ) )
				   kolv[message.type()] = 0;
			}
		}
	}
	catch(...) {};
	in.close();


	ofstream out( BINARY_DIR "/output.txt", ios:: binary ); 

	try
	{

		for( map <boost:: uint32_t, int>::const_iterator it = kolv.begin();it!=kolv.end();it++)
		{
			if (it->second!=0)
			{
				const boost:: uint32_t a = it->first;
				out.write(reinterpret_cast< const char*>(&a), sizeof(boost::uint32_t));
				const double b = static_cast< double >(it->second)/sec[it->first];
				out.write(reinterpret_cast<const char*>(&b), sizeof(double));
			}
		}
	}
	catch(exception& e)
	{
		cerr<<e.what()<<endl;
		return 1;
	}

	out.close();
	return 0;
}