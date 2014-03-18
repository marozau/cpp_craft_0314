#include <ios>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>

#include "market_message.h"

class messages_counter
{
public:

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
			uint32_t message_type = it->first;
			uint32_t avg = it->second.average();

			out.write( reinterpret_cast<char*>( &message_type ), sizeof( message_type ) );
			out.write( reinterpret_cast<char*>( &avg ), sizeof( avg ) );
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

		uint32_t average() const
		{
			if( time_num == 0 )
			{
				throw std::logic_error( "Zero occurrence. It is not possible to calc average." );
			}
			return messages_num / time_num;
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

	typedef std::map<uint32_t, uint32_t> time_counter_t;

	messages_counter counter;
	time_counter_t curr_time_messages_by_types;
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
			for( time_counter_t::iterator it = curr_time_messages_by_types.begin(); it != curr_time_messages_by_types.end(); ++it )
			{
				const uint32_t message_type = it->first;
				const uint32_t message_number = it->second;

				counter.add_count( message_type, message_number );
				counter.inc_time( it->first );
			}

			curr_time_messages_by_types.clear();
			curr_time = message.time();
		}

		curr_time_messages_by_types[ message.type() ]++;
	}

	in.close();

	std::ofstream out( BINARY_DIR "/output.txt", std::ios::out | std::ios::binary );
	counter.output_avg( out );
	out.close();
}