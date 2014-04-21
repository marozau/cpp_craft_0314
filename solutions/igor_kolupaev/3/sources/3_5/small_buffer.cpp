#include <boost/thread.hpp>

#include "averange_calculator.h"
#include "input_files_queue.h"

void do_calc()
{
	static input_files_queue queue;

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
			continue;
		}

		average_calculator calc;

		calc.calc( in );

		in.close();

		std::string output_path = BINARY_DIR + std::string( "/" ) + output_filename;
		std::ofstream out( output_path, std::ios::out | std::ios::binary );

		calc.write( out );

		out.close();
	}
}


int main()
{
	size_t max_threads = boost::thread::hardware_concurrency();

	if( max_threads == 0 )
	{
		max_threads = 2;
	}

	boost::thread_group threadpool;

	for( size_t i = 0; i < max_threads; i++ )
	{
		boost::thread *t = new boost::thread( do_calc );
		threadpool.add_thread( t );
	}

	threadpool.join_all();
}