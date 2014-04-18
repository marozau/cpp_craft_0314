#include <iostream>
#include <map>

#include "averange_calculator.h"

void average_calculator::calc( std::ifstream& in )
{
	std::map<uint32_t, size_t> size_by_types;

	time_counter_t curr_time_messages_by_types;
	uint32_t curr_time = 0;

	while( !in.eof() )
	{
		binary_reader::market_message message( in );

		if( message.eof() )
		{
			break;
		}

		if( size_by_types[ message.type() ] + message.size() > MAX_BUFF_SIZE )
		{
			continue;
		}

		if( message.time() != curr_time )
		{
			counter_.merge( curr_time_messages_by_types );

			size_by_types.clear();
			curr_time_messages_by_types.clear();
			curr_time = message.time();
		}

		curr_time_messages_by_types[ message.type() ]++;
		size_by_types[ message.type() ] += message.size();
	}

	counter_.merge( curr_time_messages_by_types );
}

void average_calculator::write( std::ofstream& out ) const
{
	try
	{
		counter_.output_avg( out );
	}
	catch( std::logic_error &error )
	{
		std::cerr << error.what();
	}
}