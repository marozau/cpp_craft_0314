
#include <iostream>
#include <string>
#include <fstream>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/lexical_cast.hpp>
#include "market_message.h"

using namespace std;

class solution
{
	static int id_;
	static const size_t threads_count = 4;
	static const int files_count = 1000;              //
	boost::mutex mtx_;


	string get_infilename(const int id)
	{
		char c[4];
		sprintf( c,"%03d", id);
		return  "/input_"+ boost:: lexical_cast<string>(c)+".txt";
	}

	string get_outfilename(const int id)
	{
		char c[4];
		sprintf( c,"%03d", id);
		return  "/output_"+ boost:: lexical_cast<string>(c)+".txt";
	}

public:

	solution() {}
	~solution() {}

	void create_thr()
	{
		boost::thread_group tg;
		for( size_t i = 0; i < threads_count; ++i )
			tg.create_thread( boost::bind( &solution::process, this ) );

		tg.join_all();
	}

	void process()
	{
		
		while (id_<files_count)
		{
			binary_reader:: binR in;
			binary_reader:: binW out;
			int curr_id = id_;
			{
				boost::mutex::scoped_lock lock( mtx_ );
		
				while(!in.is_open() && id_<files_count)
				{
					in.close();
					in.open( (BINARY_DIR+get_infilename(id_) ).c_str() );
					curr_id = id_;
					id_++;
				}

				if(!in.is_open())
					{
						cout<<"can't open" << endl;
						return ;
					}
			}

			out.open( (BINARY_DIR+get_outfilename(curr_id)).c_str() );
			boost:: uint32_t curr_time=0;
			while ( in.good() )
			{
				binary_reader:: market_message message(in); 
	
				if(!in.good())
					break;
				if( message.check(curr_time) ) 
					message.write(out);
			}
			in.close();
			out.close();
		}

	}
};

int solution:: id_=1;

int main(int argc, char* argv[]) 
{
	solution a;	 
	a.create_thr();
	return 0;
}