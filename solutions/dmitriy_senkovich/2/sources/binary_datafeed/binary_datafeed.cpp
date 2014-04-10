#include "binary_datafeed.h"

void binary_datafeed::binary_datafeed::run(){

	std::ifstream in( BINARY_DIR"/input.txt", std::ios_base::binary );
	std::ofstream out( BINARY_DIR"/output.txt", std::ios_base::binary );

	if( (!in.is_open()) || (!out.is_open()) )
		throw std::exception( "Error while opening files" );

	while( !in.eof() ){
	
		binary_reader::stock_data buff( in );

		if( in.eof() )
			break;

		buff.write( out );

		}

	in.close();
	out.close();

}