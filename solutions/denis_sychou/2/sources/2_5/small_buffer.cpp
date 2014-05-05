#include "market_message.h"
#include <fstream>
#include <map>

int main()
{
	std::ifstream in( BINARY_DIR "/input.txt", std::ios::binary );
	if ( !in.is_open() )
		return 1;
	
	typedef std::map < boost::uint32_t, size_t > type_map;

	const size_t memory = 2048, max_type = 100000;
	size_t current = 0;
	type_map type_size, type_count, type_last, type_different;

	while( !in.eof() )
	{
		binary_reader::market_message temp( in );

		if( temp.type() > max_type )
			continue;

		if( in.eof() )
			break;

		if( temp.time() != current )
		{
			type_size.clear();
			current = temp.time();
		}

		if( ( type_size[temp.type()] + temp.size() ) <= memory )
		{
			type_size[temp.type()] += temp.size();
			++type_count[temp.type()];
		}

		if( ( type_last.count( temp.type() ) == 0 ) || ( type_last[temp.type()] != current ) )
		{
			type_last[temp.type()] = current;
			++type_different[temp.type()];
		}
	}	
	in.close();
	
	std::ofstream out( BINARY_DIR "/output.txt", std::ios::binary );
	if ( !out.is_open() )
		return 1;

	for( type_map::const_iterator it = type_count.begin(); it != type_count.end(); it++ )
	{
		const double count = static_cast< double > ( it->second ) / type_different[it->first] ;
		const boost::uint32_t type = it->first;
		out.write( reinterpret_cast< const char* >( &type ), sizeof( type ) );
		out.write( reinterpret_cast< const char* >( &count ), sizeof( count ) );
	}
	out.close();

	return 0;
}