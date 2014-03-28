#include <mutex>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <thread>

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "stock_data.h"
#include "market_message_filter.h"

#include "input_files_queue.h"

namespace trades_filter
{
	static boost::mutex output_mutex_;

	void debug( const size_t thread_index, const std::string& message )
	{
		boost::mutex::scoped_lock lock( output_mutex_ );
		std::cout << "thread #" << thread_index << " " << message << std::endl;
	}

	void do_parse(const int thread_index)
	{
		static input_files_queue queue;

		const int delay = 2;

		for( ;; )
		{
			std::string input_filename, output_filename;

			try
			{
				queue.get_next( input_filename, output_filename );
			}
			catch( std::out_of_range )
			{
				break;
			}

			std::string input_path = BINARY_DIR + std::string( "/" ) + input_filename;
			std::ifstream in( input_path, std::ios::in | std::ios::binary );

			if( !in.is_open() )
			{
				debug( thread_index, input_filename + " is not found" );
				continue;
			}

			debug( thread_index, input_filename + " is opened" );

			std::string output_path= BINARY_DIR + std::string( "/" ) + output_filename;
			std::ofstream out( output_path, std::ios::out | std::ios::binary );

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

			debug( thread_index, output_filename + " is created" );

		}
	}
}

int main()
{
	size_t max_threads = std::thread::hardware_concurrency();

	if( max_threads == 0 )
	{
		max_threads = 2;
	}

	boost::thread_group threadpool;

	for( size_t i = 0; i < max_threads; i++ )
	{	
		boost::thread *t = new boost::thread( trades_filter::do_parse, i );
		t->start_thread();
		threadpool.add_thread(t);
	}

	threadpool.join_all();
}

