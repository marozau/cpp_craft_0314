#include <mutex>
#include <string>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <thread>

#include <boost/algorithm/string/replace.hpp>
#include <boost/thread/thread.hpp>

#include "stock_data.h"
#include "market_message_filter.h"

class input_files_queue
{
	const static unsigned int BEGIN_INDEX = 1;
	const static unsigned int END_INDEX = 999;

	unsigned int _last_index;

public:
	input_files_queue():_last_index( BEGIN_INDEX )
	{
	} 

	void get_next( std::string& input_filename, std::string& output_filename )
	{
		const static std::mutex queue_lock;

		if( _last_index > END_INDEX )
		{
			throw std::out_of_range( "no more files expected" );
		}

		std::ostringstream string_stream;

		string_stream << "input_";
		string_stream << std::fixed << std::setw( 3 ) << std::setfill( '0' );
		string_stream << _last_index++ << ".txt";

		input_filename = string_stream.str();
		output_filename = boost::replace_all_copy( input_filename, "input", "output" );
	}
};

void do_parse( input_files_queue& q )
{
	const int delay = 2;

	for( ;; )
	{
		std::string input_filename, output_filename;

		try
		{
			q.get_next( input_filename, output_filename );
		}
		catch( std::out_of_range )
		{
			break;
		}

		input_filename = BINARY_DIR + std::string( "/" ) + input_filename;
		std::ifstream in( input_filename, std::ios::in | std::ios::binary );

		if( !in.is_open() )
		{
			continue;
		}

		output_filename = BINARY_DIR + std::string( "/" ) + output_filename;
		std::ofstream out( output_filename, std::ios::out | std::ios::binary );

		market_message_filter filter;

		while( !in.eof() )
		{
			binary_reader::market_message message( in );

			if( in.eof() )
			{
				break;
			}

			if( filter.is_up_to_date( message, delay ) && filter.is_type_ok( message ) )
			{
				message.write( out );

				filter.update_time( message );
			}

		}

		in.close();
		out.close();
	}
}

int main()
{
	input_files_queue q;

	size_t max_threads = std::thread::hardware_concurrency();

	if( max_threads == 0 )
	{
		max_threads = 2;
	}

	boost::thread_group threadpool;


	for( size_t i = 0; i < max_threads; i++ )
	{
		threadpool.add_thread( &boost::thread( do_parse, q ) );
	}

	threadpool.join_all();
}

