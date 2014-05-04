#include <fstream>
#include "market_message.h"

int main()
{	
	std::ifstream in( BINARY_DIR "/input.txt", std::ios::binary );
	std::ofstream out ( BINARY_DIR "/output.txt", std::ios::binary );
	if ( !in.is_open() || !out.is_open() )
		return 1;

	boost::uint32_t current = 0;
	const boost::uint32_t max_type = 4, min_type = 1, time = 2;
	
	while( !in.eof() )
	{
		binary_reader::market_message temp( in );

		if( in.eof() )
			break;

		if( current < temp.time() )
			current = temp.time();

		if(  ( temp.time() + time <= current ) || ( temp.type() > max_type ) || ( temp.type() < min_type ) )
			continue;

		temp.write( out );
	}
	in.close();
	out.close();

	return 0;
}

