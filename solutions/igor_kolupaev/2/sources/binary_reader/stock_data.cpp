#include "stock_data.h"
#include "market_message.h"

binary_reader::stock_data::stock_data( std::ifstream& in )
{
	in.read( stock_name_, sizeof( stock_name_ ) );

	if( in.eof() )
	{
		// we are at the end of the stream
		eof_ = true;
		return;
	}

	eof_ = false;

	in.read( date_time_, sizeof( date_time_ ) );
	in.read( reinterpret_cast<char*>( &price_ ), sizeof( price_ ) );
	in.read( reinterpret_cast<char*>( &vwap_ ), sizeof( vwap_ ) );
	in.read( reinterpret_cast<char*>( &volume_ ), sizeof( volume_ ) );
	in.read( reinterpret_cast<char*>( &f1_ ), sizeof( f1_ ) );
	in.read( reinterpret_cast<char*>( &t1_ ), sizeof( t1_ ) );
	in.read( reinterpret_cast<char*>( &f2_ ), sizeof( f2_ ) );
	in.read( reinterpret_cast<char*>( &f3_ ), sizeof( f3_ ) );
	in.read( reinterpret_cast<char*>( &f4_ ), sizeof( f4_ ) );
}

binary_reader::stock_data::stock_data(
	const char* stock_name,
	const char* date_time,
	const double price,
	const double vwap,
	const boost::uint32_t volume,
	const double f1,
	const double t1,
	const double f2,
	const double f3,
	const double f4 ):

	price_( price ),
	vwap_( vwap ),
	volume_( volume ),
	f1_( f1 ),
	t1_( t1 ),
	f2_( f2 ),
	f3_( f3 ),
	f4_( f4 ),
	eof_( false )
{
	strncpy( stock_name_, stock_name, sizeof( stock_name_ ) );
	strncpy( date_time_, date_time, sizeof( date_time_ ) );
}

binary_reader::stock_data::~stock_data()
{
}

void binary_reader::stock_data::write( std::ofstream& out ) const
{
	boost::uint32_t date = 0;
	int month;
	int day;
	int year;
	std::sscanf( date_time_, "%4d%2d%2d", &year, &month, &day );
	date = ( year - 1 ) * 372 + ( month - 1 ) * 31 + day;

	static char stock_name[ 9 ];
	memcpy( stock_name, stock_name_, sizeof( stock_name_ ) );
	binary_write( out, stock_name );
	binary_write( out, date );
	binary_write( out, vwap_ );
	binary_write( out, volume_ );
	binary_write( out, f2_ );
}

void binary_reader::stock_data::write_raw( std::ofstream& out ) const
{
	binary_write( out, stock_name_ );
	binary_write( out, date_time_ );
	binary_write( out, price_ );
	binary_write( out, vwap_ );
	binary_write( out, volume_ );
	binary_write( out, f1_ );
	binary_write( out, t1_ );
	binary_write( out, f2_ );
	binary_write( out, f3_ );
	binary_write( out, f4_ );
}
