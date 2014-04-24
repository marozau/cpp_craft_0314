#include <iostream>
#include <string>
#include <fstream>
#include <stdint.h>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <map>
#include "stock_data.h"

using namespace std;
typedef map <std:: string, boost::shared_ptr <binary_reader::binW> > m_s_shp;

class solution
{
	binary_reader::binR in_;
	static int id;
	m_s_shp data;

	string get_outfilename(const string stock_name)
	{
		return  "/output_"+ stock_name+".txt";
	}

public:

	solution() 
	{
		in_.open( BINARY_DIR"/input.txt");
		if(!in_.is_open())
			 throw logic_error("Can't open input.txt");
	}
	~solution() 
	{
		in_.close(); 
	}

	void process()
	{
		string stock_name;
		while ( in_.good() )
		{
			binary_reader:: stock_data message(in_);
			if(!in_.good()) 
			{
				break;
			}
			stock_name = boost:: lexical_cast <string> (message.get_stock_name());
			if(data.find(stock_name) == data.end())
			{
				boost::shared_ptr< binary_reader::binW > binw_ptr( new binary_reader::binW );
				binw_ptr->open(( BINARY_DIR+get_outfilename( stock_name ) ).c_str() , true );
				data[stock_name] = binw_ptr;
			}

			message.write(*data[stock_name]);
			
		}
		for (m_s_shp:: const_iterator im = data.begin(); im!= data.end(); ++im)
			(im->second)->close();
	}

};



int main(int argc, char* argv[]) 
{
	try
	{
		solution a;	 
		a.process();
	}
	catch(exception& e)
	{
		cerr<<e.what()<<endl;
	}
	return 0;
}