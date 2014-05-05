#include "binary_datafeed.h"
#include <iostream>
#include <boost/lexical_cast.hpp>

string get_outfilename(const string file)
{
	return "/output_" + file + ".txt";
}

void task3_6::solution::close_all_ofstreams_in_map_(map_type& map_name)
{
	for(map_type::iterator iter = map_name.begin(); iter != map_name.end(); ++iter)
	{
		(*(*iter).second).close();
	}
}

void task3_6::solution::start()
{
	static const char* inp_file = BINARY_DIR "/input.txt";
	ifstream input_file(inp_file, ios::binary);

	if (!input_file.is_open())
	{
		cout << "Could not open input file" << endl;
		return;
	}

	try
	{    
		while (!input_file.eof())
		{
			binary_reader::stock_data st_data(input_file);
			if (input_file.eof()) 
				break;
			const string stock_name = boost:: lexical_cast<string>(st_data.stock_name());
			if(map_name_stream_.count(stock_name) == 0)
			{
				const string outp_file = BINARY_DIR + get_outfilename(boost:: lexical_cast<string>(stock_name));
				map_name_stream_[stock_name] = boost::make_shared<std::ofstream>(outp_file.c_str(), std::ios::binary);
			}
			st_data.write(*map_name_stream_[stock_name]);
		}
	}
	catch(...) 
	{
		input_file.close();
		close_all_ofstreams_in_map_(map_name_stream_);
	}

	input_file.close();
	close_all_ofstreams_in_map_(map_name_stream_);
}

