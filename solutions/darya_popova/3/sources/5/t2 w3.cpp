
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/lexical_cast.hpp>
#include <algorithm>
#include "market_message.h"

using namespace std;

class solution
{
	static int id_;
	static const size_t threads_count = 4;
	static const int files_count = 1000;               //
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

	void create_thr_write()
	{
		boost::thread_group tg;
		for( size_t i = 0; i < threads_count; ++i )
			tg.create_thread( boost::bind( &solution::process, this ) );

		tg.join_all();
	}

	void process()
	{
		int curr_id = id_;
		while (id_<files_count)
		{
			binary_reader:: binR in;
			{
				boost::mutex::scoped_lock lock( mtx_ );
		
				while(!in.is_open() && id_<files_count)
				{
					in.open( (BINARY_DIR+get_infilename(id_) ).c_str() );
					curr_id = id_;
					id_++;
				}

					if(!in.is_open())
				{
					cout<<"cant't open file"<< id_ <<endl;
						return ;
				}
			}
			map < boost:: uint32_t, int> sec, kolv;
			map < boost::uint32_t, size_t> size;
			map <boost:: uint32_t, boost:: uint32_t> last;
			binary_reader:: market_message message(in);
			if (message.check_size(size))
			{
				kolv[message.type()]++;
				size[message.type()]+= message.get_size();
			}
			else 
			{
				kolv[message.type()]=0;
			}
			
			{
			last[message.type()] = message.time();
			sec[message.type()]++;
			}

			while ( in.good() )
			{
				binary_reader:: market_message message(in); 
				if(!in.good())
					break;
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
				}
				if(!kolv.count( message.type()) )
				{
					kolv[message.type()] = 0;
				}
				ofstream out(BINARY_DIR+get_outfilename(curr_id) );
				for( map <boost:: uint32_t, int>::const_iterator it = kolv.begin();it!=kolv.end(); ++it)
				{
					if (it->second!=0)
					{
						const boost:: uint32_t a = it->first;
						out.write(reinterpret_cast< const char*>(&a), sizeof(boost::uint32_t));
						const double b = static_cast< double >(it->second)/sec[it->first];
						out.write(reinterpret_cast< const char*>(&b), sizeof(double));
		
					}
				}

				out.close();
			}
			in.close();
		}
	}
};

int solution:: id_=1;

int main(int argc, char* argv[]) 
{
	solution a;	 
	a.create_thr_write();
	system("pause");
	return 0;
}