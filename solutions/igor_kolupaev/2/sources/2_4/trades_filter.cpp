#include <ios>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

#include "market_message.h"

class market_message_filter
{
public:
	const static uint32_t MARKET_OPEN = 1u;
	const static uint32_t TRADE = 2u;
	const static uint32_t QUOTE = 3u;
	const static uint32_t MARKET_CLOSE = 4u;

	market_message_filter(): _current_time( 0 )
	{
		_good_types.insert( MARKET_OPEN );
		_good_types.insert( TRADE );
		_good_types.insert( QUOTE );
		_good_types.insert( MARKET_CLOSE );
	}

	bool is_up_to_date( const binary_reader::market_message& message, uint32_t delay ) const
	{
		return _current_time < message.time() + delay;
	}

	bool is_type_ok( const binary_reader::market_message& message ) const
	{
		return _good_types.count( message.type() ) > 0;
	}

	void update_time( const binary_reader::market_message& message )
	{
		if( _current_time < message.time() )
		{
			_current_time = message.time();
		}
	}

	uint32_t current_time() const
	{
		return _current_time;
	}

private:
	uint32_t _current_time;

	std::set<uint32_t> _good_types;
};

int main()
{
	const int delay = 2;

	std::ifstream in( BINARY_DIR "/input.txt", std::ios::in | std::ios::binary );

	if( !in.is_open() )
	{
		std::cerr << "Unable to open input.txt";
		return 1;
	}

	std::ofstream out( BINARY_DIR "/output.txt", std::ios::out | std::ios::binary );

	market_message_filter filter;

	while( !in.eof() )
	{
		binary_reader::market_message message( in );

		if( message.eof() )
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