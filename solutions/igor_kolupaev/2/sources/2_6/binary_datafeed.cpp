#include <ios>
#include <fstream>
#include <iostream>

#include "stock_data.h"

class stock_data_short
{
	char stock_name_[ 9 ];
	boost::uint_fast32_t date_time_;
	double price_;
	boost::uint32_t volume_;
	double f2_;

	boost::uint32_t date_as_uint( const char date_time[ 8 ] )
	{
		unsigned int year, month, day;

		std::sscanf( date_time, "%4d%2d%2d", &year, &month, &day );

		const boost::uint32_t ret_date_time = ( year - 1 ) * 372 + ( month - 1 ) * 31 + day;

		return ret_date_time;
	}

	void set_stock_name( const char *new_stock_name )
	{
		memset( stock_name_, 0, sizeof( stock_name_ ) );
		size_t len = strlen( new_stock_name );
		if( len > sizeof( stock_name_ ) )
		{
			len = sizeof(stock_name_) -1;
		}

		strncpy( stock_name_, new_stock_name, len );
	};

public:

	stock_data_short():
		date_time_( 0 ),
		price_( 0 ),
		volume_( 0 ),
		f2_( 0 )
	{
		set_stock_name( "" );
	}

	stock_data_short( binary_reader::stock_data& data )
	{
		set_stock_name( data.stock_name() );
		date_time_ = date_as_uint( data.date_time() );
		price_ = data.vwap();
		volume_ = data.volume();
		f2_ = data.f2();
	};

	void write( std::ofstream& out ) const
	{
		out.write( stock_name_, sizeof( stock_name_ ) );
		out.write( reinterpret_cast<const char*>( &date_time_ ), sizeof( date_time_ ) );
		out.write( reinterpret_cast<const char*>( &price_ ), sizeof( price_ ) );
		out.write( reinterpret_cast<const char*>( &volume_ ), sizeof( volume_ ) );
		out.write( reinterpret_cast<const char*>( &f2_ ), sizeof( f2_ ) );
	}

	void read( std::ifstream& in )
	{
		in.read( stock_name_, sizeof( stock_name_ ) );
		in.read( reinterpret_cast<char*>( &date_time_ ), sizeof( date_time_ ) );
		in.read( reinterpret_cast<char*>( &price_ ), sizeof( price_ ) );
		in.read( reinterpret_cast<char*>( &volume_ ), sizeof( volume_ ) );
		in.read( reinterpret_cast<char*>( &f2_ ), sizeof( f2_ ) );
	}
};

int main()
{
	std::ifstream in( BINARY_DIR "/input.txt", std::ios::in | std::ios::binary );

	if( !in.is_open() )
	{
		std::cerr << "Unable to open input.txt";
		return 1;
	}

	std::ofstream out( BINARY_DIR "/output.txt", std::ios::out | std::ios::binary );
	while( !in.eof() )
	{
		binary_reader::stock_data data( in );

		if( data.eof() )
		{
			break;
		}

		stock_data_short data1( data );
		data1.write( out );
	}

	out.close();
	in.close();
}

