
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
	return (( size[a.type()] + get_size(a))<binary_reader:: market_message::buffer_size);
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
			binary_reader:: market_message st(in); 
			if (check_size(size, st))
		{
			kolv[st.type()]++;
			size[st.type()]+= get_size(st);
		}
		else 
			kolv[st.type()]=0;

		sec[st.type()]=1;
		last[st.type()] = st.time();
		

		while ( in.good() )
		{
			binary_reader:: market_message st(in); 
			if(!in.good()) break;
			if ( last[st.type()]==st.time() && check_size(size, st) ) 
			{
				size[st.type()]+= get_size(st); 
				kolv[st.type()]++;
			}
			else 
				if( last[st.type()]!=st.time() )
				{
					sec[st.type()]++;
					kolv[st.type()]++;
					size[st.type()] = 0;
					last[st.type()] = st.time();
				}
				   
				if(!kolv.count( st.type() ) )
				   kolv[st.type()] = 0;
			 }
	}
	catch(...) {};
	in.close();


	ofstream out( BINARY_DIR "/output.txt", ios:: binary ); 

	try
	{

		for( map <boost:: uint32_t, int>::iterator it = kolv.begin();it!=kolv.end();it++)
		{
			if (it->second!=0)
			{
				boost:: uint32_t a= (it->first);
				out.write(reinterpret_cast<char*>(&a), sizeof(boost::uint32_t));
				double b = static_cast< double >(it->second)/sec[it->first];
				out.write(reinterpret_cast<char*>(&b), sizeof(double));
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