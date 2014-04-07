#include "trade_filter.h"

void trade_filter::trade_filter::run(){

	const enum types { type1 = 1u, type2 = 2u, type3 = 3u, type4 = 4u };

	std::ifstream in( BINARY_DIR"/input.txt", std::ios_base::binary );
	std::ofstream out( BINARY_DIR"/output.txt", std::ios_base::binary );

	if( (!in.is_open()) || (!out.is_open()) )
		throw std::exception( "Error while opening files" );

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