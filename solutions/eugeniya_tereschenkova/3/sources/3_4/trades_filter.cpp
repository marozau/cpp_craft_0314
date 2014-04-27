#include "market_message.h"
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
using namespace std;

namespace Constants_3_4
{
	static const boost::uint32_t type_min = 1u;
	static const boost::uint32_t type_max = 4u;
	static const long long N = static_cast<long long>(pow(10.0,16.0));
}

bool is_good_type (const boost::uint32_t type, const boost::uint32_t type_min, const boost::uint32_t type_max)
{
	return ((type >= type_min) && (type <= type_max)) ;
}

string get_infilename(const int file_number)
{
	char id[4];
	sprintf_s( id, 4, "%03d", file_number);
	return  "/input_"+ boost:: lexical_cast<string>(id)+".txt";
}

string get_outfilename(const int file_number)
{
	char id[4];
	sprintf_s( id, 4, "%03d", file_number);
	return  "/output_"+ boost:: lexical_cast<string>(id)+".txt";
}

void process_file( const int file_number)
{
	boost::uint32_t cur_time = 0;
	int mes_count = 0;

	const string inp_file = BINARY_DIR + get_infilename(file_number);

	ifstream input_file(inp_file.c_str(), ios::binary);
	if (!input_file.is_open())
	{
		return;
	}

	const string outp_file = BINARY_DIR + get_outfilename(file_number);
	ofstream output_file(outp_file.c_str(), ios::binary);

	try
	{    
		while (!input_file.eof())
		{
			if(mes_count > Constants_3_4::N)
				throw logic_error("Input is incorrect count messages");
			binary_reader::market_message mark_mes(input_file);
			if (input_file.eof()) 
				break;
			if( mark_mes.check_time(cur_time) && is_good_type(mark_mes.type(), Constants_3_4::type_min, Constants_3_4::type_max))
				mark_mes.write(output_file);
			mes_count++;
		}
	}
	catch(...) 
	{
		input_file.close();
		output_file.close();
	};

	input_file.close();
	output_file.close();
}

int main()
{
	boost::thread_group group_threads;
	static const int file_count = 999;

	for (int i = 1; i <= file_count; ++i)
	{
		group_threads.create_thread( boost::bind( &process_file, i ));
	}

	group_threads.join_all();

	return 0;
}