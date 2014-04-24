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

class solution
{
	binary_reader::binR in_;
	static int id;
	//static const size_t threads_count = 4;
	//boost::mutex mtx_;

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

	//void create_thr()
	//{
	//	boost::thread_group tg;
	//	for( size_t i = 0; i < threads_count; ++i )
	//		tg.create_thread( boost::bind( &solution::process, this ) );

	//	tg.join_all();

	//}

	void process()
	{
			while ( in_.good() )
			{
				//boost::mutex::scoped_lock lock( mtx_ );
				binary_reader:: stock_data message(in_);
				if(!in_.good()) 
				{
					break;
				}
				cout<< message.get_stock_name()<< endl;
				string a= boost:: lexical_cast <string> (message.get_stock_name());

				binary_reader:: binW out;
				out.open(   ( BINARY_DIR+get_outfilename( a ) ).c_str() , true );

				message.write( out );
				out.close();
			}
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