#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include "market_message.h"

using namespace std;

size_t get_size( binary_reader:: market_message& a)
{
	return (sizeof(a.type()) + sizeof(a.time()) + sizeof(a.len()) + sizeof(char)*a.len());
}

bool check_size( map <boost:: uint32_t, size_t> size, binary_reader:: market_message& a)
{
	return (( size[a.type()] + get_size(a))<=2048);
}

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
		binary_reader:: market_message start(in); 
		if (check_size(size, start))
		{
			kolv[start.type()]++;
			size[start.type()]+= get_size(start);
		}
		else 
			kolv[start.type()]=0;

		sec[start.type()]=1;
		last[start.type()] = start.time();
		

		while ( in.good() )
		{
			binary_reader:: market_message start(in); 
			if(!in.good()) break;
			if ( last[start.type()]==start.time() && check_size(size, start) ) 
			{
				size[start.type()]+= get_size(start); 
				kolv[start.type()]++;
			}
			else 
				if( last[start.type()]!=start.time() )
				{
					sec[start.type()]++;
					size[start.type()] = 0;
					last[start.type()] = start.time();
				}
				   
				if(!kolv.count( start.type() ) )
				   kolv[start.type()] = 0;
			 }
	}
	catch(...) {};
	in.close();


	ofstream out( BINARY_DIR "/output.txt", ios:: binary ); 

	try
	{

		for( map <boost:: uint32_t, int>::iterator it = kolv.begin();it!=kolv.end();it++)
			 out<<it->first<<double(it->second)/sec[it->first];
	}
	catch(exception& e)
	{
		cerr<<e.what()<<endl;
		return 1;
	}

	out.close();
	return 0;
}