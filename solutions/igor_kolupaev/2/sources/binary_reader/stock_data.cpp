#include "stock_data.h"

binary_reader::stock_data::stock_data( std::ifstream& in )
{
	in.read( stock_name_, sizeof( stock_name_ ) );

	if( in.eof() )
	{
		// we are at the end of the stream
		_eof = true;
		return;
	}

	_eof = false;

	in.read( date_time_, sizeof( date_time_ ) );
	in.read( (char *) ( &price_ ), sizeof( price_ ) );
	in.read( (char *) ( &vwap_ ), sizeof( vwap_ ) );
	in.read( (char *) ( &volume_ ), sizeof( volume_ ) );
	in.read( (char *) ( &f1_ ), sizeof( f1_ ) );
	in.read( (char *) ( &t1_ ), sizeof( t1_ ) );
	in.read( (char *) ( &f2_ ), sizeof( f2_ ) );
	in.read( (char *) ( &f3_ ), sizeof( f3_ ) );
	in.read( (char *) ( &f4_ ), sizeof( f4_ ) );
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
	const double f4 )
{
	_eof = false;

	strncpy( stock_name_, stock_name, sizeof( stock_name_ ) );
	strncpy( date_time_, date_time, sizeof( date_time_ ) );

	price_ = price;
	vwap_ = vwap;
	volume_ = volume;
	f1_ = f1;
	t1_ = t1;
	f2_ = f2;
	f3_ = f3;
	f3_ = f3;
}

binary_reader::stock_data::~stock_data()
{
}

void binary_reader::stock_data::write( std::ofstream& out )
{
	out.write( stock_name_, sizeof( stock_name_ ) );
	out.write( date_time_, sizeof( date_time_ ) );
	out.write( (char *) ( &price_ ), sizeof( price_ ) );
	out.write( (char *) ( &vwap_ ), sizeof( vwap_ ) );
	out.write( (char *) ( &volume_ ), sizeof( volume_ ) );
	out.write( (char *) ( &f1_ ), sizeof( f1_ ) );
	out.write( (char *) ( &t1_ ), sizeof( t1_ ) );
	out.write( (char *) ( &f2_ ), sizeof( f2_ ) );
	out.write( (char *) ( &f3_ ), sizeof( f3_ ) );
	out.write( (char *) ( &f4_ ), sizeof( f4_ ) );
}

void binary_reader::stock_data::write_raw( std::ofstream& out )
{
	// your code. Can be emty
	// this method is used for testing. It writes data to the binary file without convertion.
}
