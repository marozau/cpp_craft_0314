#include "market_message.h"
#include "trades_filter.h"
#include <iostream>
#include <boost/lexical_cast.hpp>
using namespace std;

bool is_good_type (const boost::uint32_t type, const boost::uint32_t type_min, const boost::uint32_t type_max)
{
	return ((type >= type_min) && (type <= type_max)) ;
}

string get_infilename(const int file_number)
{
	stringstream strstream;
	strstream.width(3);
	strstream<<setfill('0');
	strstream<<file_number;
	string id;
	strstream>>id;
	return "/input_" + id + ".txt";
}

string get_outfilename(const int file_number)
{
	stringstream strstream;
	strstream.width(3);
	strstream<<setfill('0');
	strstream<<file_number;
	string id;
	strstream>>id;
	return "/output_" + id + ".txt";
}

task3_4::solution::solution( const int files_count ):files_count_(files_count)
{
}

void task3_4::solution::process_file_()
{  
  	while(true)
  	{
		boost::mutex::scoped_lock lock_file_(task3_4::solution::wait_file_);
		if(files_count_ < 1)
		{
  			lock_file_.unlock();
  			break;
		}
	  	const string inp_file = BINARY_DIR + get_infilename(files_count_);
	  	const string outp_file = BINARY_DIR + get_outfilename(files_count_);

		--files_count_;
		lock_file_.unlock();

	  	ifstream input_file(inp_file.c_str(), ios::binary);
	  	if (!input_file.is_open())
	  	{
  			continue;
	  	}

	  	ofstream output_file(outp_file.c_str(), ios::binary);

	  	try
	  	{    
    		boost::uint32_t cur_time = 0;
    		int mes_count = 0;
		  	while (!input_file.eof())
		  	{
			  	if(mes_count > task3_4::N)
					throw logic_error("Input is incorrect count messages");
			  	binary_reader::market_message mark_mes(input_file);
			  	if (input_file.eof()) 
					break;
			  	if( mark_mes.check_time(cur_time) && is_good_type(mark_mes.type(), task3_4::type_min, task3_4::type_max))
					mark_mes.write(output_file);
			  	mes_count++;
		  	}
	  	}
	  	catch(...) 
	  	{
			input_file.close();
		  	output_file.close();
		  	continue;
	  	};

	  	input_file.close();
	  	output_file.close();
  	}
}

void task3_4::solution::start()
{
  	boost::thread_group group_threads;
  	static const int threads_count = 4;

	for (int i = 0; i < threads_count; ++i)
	{
		group_threads.create_thread( boost::bind( &task3_4::solution::process_file_, this ));
	}

	group_threads.join_all();
}
