#include "trade_filter.h"
#include <string>
#include <iostream>
#include <boost/thread.hpp>

void trade_filter::trade_filter::run( const std::string& input, const std::string& output )
{

	const enum types { type1 = 1u, type2 = 2u, type3 = 3u, type4 = 4u };

	std::ifstream in( input.c_str(), std::ios_base::binary );

	if( !in.is_open() )
		throw std::exception( "Error while opening input file " );
	
	std::ofstream out( output.c_str(), std::ios_base::binary );

	if( !out.is_open() )
		throw std::exception( "Error while opening output file " );

	boost::uint32_t max_curr_time;

	binary_reader::market_message buff( in );

	max_curr_time = buff.time();

	if( !( ( buff.type() != type1 ) && ( buff.type() != type2 ) && ( buff.type() != type3 ) && ( buff.type() != type4 ) ) )
		buff.write( out );

	while( true )
	{
		std::streamoff pos = in.tellg();
		in.get();
		if(in.eof())
			break;
		in.seekg(pos);

		binary_reader::market_message buff( in );

		if( ( buff.type() != type1 ) && ( buff.type() != type2 ) && ( buff.type() != type3 ) && ( buff.type() != type4 ) )
			continue;

		if( buff.time() > max_curr_time )
			max_curr_time = buff.time();

		if( max_curr_time < 2 )
			buff.write( out );
		else
		{
			if( buff.time() <= (max_curr_time - 2) )
				continue;
			else
				buff.write( out );
		}
	}

	in.close();
	out.close();

}