#include "th_binary_datafeed.h"
#include <boost/lexical_cast.hpp>

namespace th_binary_datafeed
{
	th_binary_datafeed::th_binary_datafeed()
	{
	}
	void th_binary_datafeed::read_set_threads_and_run_process()
	{
		std::ifstream in( BINARY_DIR"/input.txt", std::ios_base::binary );

		if( !in.is_open() )
			throw std::exception( "Error while opening input file\n" );

		while( true )
		{
			std::streamoff pos = in.tellg();
			in.get();
			if( in.eof() )
				break;
			in.seekg( pos );

			binary_reader::stock_data buff_msg( in );

			data_storage_[std::string( buff_msg.stock_name() )].push_back( buff_msg );
		}

		in.close();
		
		data_iter_ = data_storage_.begin();

		set_threads_and_run_process();
	}
	void th_binary_datafeed::set_threads_and_run_process()
	{
		for( size_t i = 0; i < thread_count_; i++ )
			th_gr_.create_thread( boost::bind( &th_binary_datafeed::process, this ) );
		
		th_gr_.join_all();
	}
	void th_binary_datafeed::process()
	{
		while( true )
		{
			data_map::iterator temp_map_iter;
			{
				boost::mutex::scoped_lock lock( mtx_ );
				{
					if( data_iter_ == data_storage_.end() )
						break;
					temp_map_iter = data_iter_++;
				}
			}

			std::string file_name = BINARY_DIR"/output_" + temp_map_iter->first + ".txt";

			std::ofstream out( file_name.c_str(), std::ios_base::binary );

			try
			{
				if( !out.is_open() )
					throw std::exception( "Error while opening output file " );
			}
			catch( std::exception& e )
			{
				boost::mutex::scoped_lock lock( mtx_ );
				{
					std::cerr << e.what() << file_name.c_str() << "\n";
					return;
				}
			}

			msg_iter temp_msg_iter = temp_map_iter->second.begin();

			while( temp_msg_iter != temp_map_iter->second.end() )
			{
				try
				{
					temp_msg_iter->write( out );
				}
				catch( std::exception& e )
				{
					boost::mutex::scoped_lock lock( mtx_ );
					{
						std::cerr << e.what() << file_name.c_str() << "\n";
						return;
					}
				}
				temp_msg_iter++;
			}

			out.close();
		}
	}
}