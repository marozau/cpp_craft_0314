#include "stock_data.h"

int main()
{
	std::ifstream in( BINARY_DIR "/input.txt", std::ios::binary );
	std::ofstream out ( BINARY_DIR "/output.txt", std::ios::binary );

	if ( !in.is_open() || !out.is_open() )
		return 1;

	while( !in.eof() )
	{
		binary_reader::stock_data temp( in );

		if( in.eof() )
			break;

		temp.write( out );
	}
	in.close();
	out.close();

	return 0;
}

