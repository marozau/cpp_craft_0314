#include "stock_data.h"

binary_reader::stock_data::stock_data( std::ifstream& in )
{
	if ( !in.read( stock_name_, sizeof(char)*stock_size ) )
		throw std::exception( "Error while reading data\n" );
	if ( !in.read( date_time_, sizeof(char)*date_size ) )
		throw std::exception( "Error while reading data\n" );
	if ( !in.read( reinterpret_cast<char*> (&price_), sizeof(double) ) )
		throw std::exception( "Error while reading data\n" );
	if ( !in.read( reinterpret_cast<char*> (&vwap_), sizeof(double) ) )
		throw std::exception( "Error while reading data\n" );
	if ( !in.read( reinterpret_cast<char*> (&volume_), sizeof( boost::uint32_t ) ) )
		throw std::exception( "Error while reading data\n" );
	if ( !in.read( reinterpret_cast<char*> (&f1_), sizeof(double) ) )
		throw std::exception( "Error while reading data\n" );
	if ( !in.read( reinterpret_cast<char*> (&t1_), sizeof(double) ) )
		throw std::exception( "Error while reading data\n" );
	if ( !in.read( reinterpret_cast<char*> (&f2_), sizeof(double) ) )
		throw std::exception( "Error while reading data\n" );
	if ( !in.read( reinterpret_cast<char*> (&f3_), sizeof(double) ) )
		throw std::exception( "Error while reading data\n" );
	if ( !in.read( reinterpret_cast<char*> (&f4_), sizeof(double) ) )
		throw std::exception( "Error while reading data\n" );
}
binary_reader::stock_data::stock_data( const char* stock_name,
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
	memcpy( stock_name_, stock_name, sizeof( char )*stock_size );
	memcpy( date_time_, date_time, sizeof( char )*date_size );
	price_ = price;
	volume_ = volume;
	f1_ = f1;
	t1_ = t1;
	f2_ = f2;
	f3_ = f3;
	f4_ = f4;
}
binary_reader::stock_data::~stock_data()
{

}
void binary_reader::stock_data::write( std::ofstream& out )
{
	if ( !out.write( stock_name_, sizeof(char)*(stock_size+1) ) )
		throw std::exception( "Error while writing data\n" );
	int year_, month_, day_;
	sscanf( date_time_, "%4d%2d%2d", &year_, &month_, &day_ );
	boost::uint32_t day_time_ = 372*(year_-1) + 31*(month_-1) + day_;
	if ( !out.write( reinterpret_cast<char*> (&day_time_), sizeof( boost::uint32_t ) ) )
		throw std::exception( "Error while writing data\n" );
	if ( !out.write( reinterpret_cast<char*> (&vwap_), sizeof(double) ) )
		throw std::exception( "Error while writing data\n" );
	if ( !out.write( reinterpret_cast<char*> (&volume_), sizeof( boost::uint32_t ) ) )
		throw std::exception( "Error while writing data\n" );
	if ( !out.write( reinterpret_cast<char*> (&f2_), sizeof(double) ) )
		throw std::exception( "Error while writing data\n" );
}
