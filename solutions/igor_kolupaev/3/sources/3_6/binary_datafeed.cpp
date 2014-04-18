#include <iostream>
#include <map>
#include <string>

#include <stock_data.h>

class out_streams
{
	std::map<std::string, std::ofstream*> streams_;

public:

	out_streams()
	{
	}

	~out_streams()
	{
		for( auto it = streams_.begin(); it != streams_.end(); it++ )
		{
			it->second->close();
		}
	}

	std::ofstream* get_for( const char *stock_name ) 
	{
		const std::string stock_name_str( stock_name );

		if( streams_.count( stock_name_str ) == 0 )
		{
			std::ofstream *p_stream = new std::ofstream( BINARY_DIR "/output_" + stock_name_str + ".txt", std::ios::binary );
			streams_[ stock_name_str ] = p_stream;
		}

		return streams_[ stock_name_str ];
	}
};

int main()
{
	std::ifstream in( BINARY_DIR "/input.txt", std::ios::binary );

	if( !in.is_open() )
	{
		std::cerr << "Unable to open input.txt";
		return 1;
	}

	out_streams streams;

	while( !in.eof() )
	{
		binary_reader::stock_data data( in );

		if( data.eof() )
		{
			break;
		}

		std::ofstream *out = streams.get_for( data.stock_name() );
		data.write( *out );
	}

	in.close();
}

