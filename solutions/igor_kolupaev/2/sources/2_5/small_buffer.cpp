#include <ios>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>

#include "market_message.h"

class messages_counter
{
public:

	typedef std::map<uint32_t, uint32_t> time_counter_t;

	void merge( const time_counter_t& second_counter )
	{
		for( time_counter_t::const_iterator it = second_counter.begin();
			 it != second_counter.end();
			 ++it )
		{
			const uint32_t message_type = it->first;
			const uint32_t message_number = it->second;

			add_count( message_type, message_number );
			inc_time( it->first );
		}
	}

	void inc_time( const uint32_t message_type )
	{
		++( _data[ message_type ].time_num );
	}

	void add_count( const uint32_t message_type, const uint32_t number )
	{
		_data[ message_type ].messages_num += number;
	}

	void output_avg( std::ostream& out )
	{
		for( msg_map_t::iterator it = _data.begin(); it != _data.end(); ++it )
		{
			const uint32_t message_type = it->first;
			const double avg = it->second.average();

			binary_reader::binary_write( out, message_type );  
			binary_reader::binary_write( out, avg );
		}
	}

private:

	struct messages_data_t
	{
		messages_data_t(): messages_num( 0 ), time_num( 0 )
		{
		};

		uint32_t messages_num;
		uint32_t time_num;

		double average() const
		{
			if( time_num == 0 )
			{
				throw std::logic_error( "Zero occurrence. It is not possible to calc average." );
			}
			return static_cast<double>( messages_num ) / time_num;
		};
	};

	typedef std::map<uint32_t, messages_data_t> msg_map_t;

	msg_map_t _data;
};



int main()
{
	std::ifstream in( BINARY_DIR "/input.txt", std::ios::in | std::ios::binary );

	if( !in.is_open() )
	{
		std::cerr << "Unable to open input.txt";
		return 1;
	}

	messages_counter counter;
	messages_counter::time_counter_t curr_time_messages_by_types;
	uint32_t curr_time = 0;

	while( !in.eof() )
	{
		binary_reader::market_message message( in );

		if( message.eof() )
		{
			break;
		}

		if( message.time() != curr_time )
		{
			counter.merge( curr_time_messages_by_types );

			curr_time_messages_by_types.clear();
			curr_time = message.time();
		}

		curr_time_messages_by_types[ message.type() ]++;
	}

	in.close();

	counter.merge( curr_time_messages_by_types );

	std::ofstream out( BINARY_DIR "/output.txt", std::ios::out | std::ios::binary );

	try
	{
		counter.output_avg( out );
	}
	catch( std::logic_error &error )
	{
		std::cerr << error.what();
	}

	out.close();
}