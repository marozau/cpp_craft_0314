#include "messages_counter.h"

messages_data_t::messages_data_t(): messages_num( 0 ), time_num( 0 )
{
};

double messages_data_t::average() const
{
	if( time_num == 0 )
	{
		throw std::logic_error( "Zero occurrence. It is not possible to calc average." );
	}
	return static_cast<double>( messages_num ) / time_num;
};

void messages_counter::merge( const time_counter_t& second_counter )
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

void messages_counter::inc_time( const uint32_t message_type )
{
	++( _data[ message_type ].time_num );
}

void messages_counter::add_count( const uint32_t message_type, const uint32_t number )
{
	_data[ message_type ].messages_num += number;
}

void messages_counter::output_avg( std::ostream& out ) const
{
	for( msg_map_t::const_iterator it = _data.begin(); it != _data.end(); ++it )
	{
		const uint32_t message_type = it->first;
		const double avg = it->second.average();

		binary_reader::binary_write( out, message_type );
		binary_reader::binary_write( out, avg );
	}
}


