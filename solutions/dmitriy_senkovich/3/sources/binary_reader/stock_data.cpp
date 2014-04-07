#include "stock_data.h"

binary_reader::stock_data::stock_data( std::ifstream& in )
{
	stock_name_ = new char [9];
	date_time_ = new char [9];
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
	stock_name_[8] = '\0';
	date_time_[8] = '\0';
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
	memcpy( stock_name_, stock_name, sizeof( char )*( stock_size + 1 ) );
	memcpy( date_time_, date_time, sizeof( char )*( date_size + 1 ) );
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
	delete stock_name_;
	delete date_time_;
}
void binary_reader::stock_data::write( std::ofstream& out )
{
	if ( !out.write( stock_name_, sizeof(char)*(stock_size+1) ) )
		throw std::exception( "Error while writing data in file " );
	int year_, month_, day_;
	sscanf( date_time_, "%4d%2d%2d", &year_, &month_, &day_ );
	boost::uint32_t day_time_ = 372*(year_-1) + 31*(month_-1) + day_;
	if ( !out.write( reinterpret_cast<char*> (&day_time_), sizeof( boost::uint32_t ) ) )
		throw std::exception( "Error while writing data in file " );
	if ( !out.write( reinterpret_cast<char*> (&vwap_), sizeof(double) ) )
		throw std::exception( "Error while writing data in file " );
	if ( !out.write( reinterpret_cast<char*> (&volume_), sizeof( boost::uint32_t ) ) )
		throw std::exception( "Error while writing data in file " );
	if ( !out.write( reinterpret_cast<char*> (&f2_), sizeof(double) ) )
		throw std::exception( "Error while writing data in file " );
}
char* binary_reader::stock_data::stock_name()
{
	return stock_name_;
}
binary_reader::stock_data::stock_data( const stock_data& buff )
{
	stock_name_ = new char [9];
	date_time_ = new char [9];
	memcpy( stock_name_, buff.stock_name_, 9 );
	memcpy( date_time_, buff.date_time_, 9 );
	price_ = buff.price_;
	vwap_ = buff.vwap_;
	volume_ = buff.volume_;
	f1_ = buff.f1_;
	f2_ = buff.f2_;
	f3_ = buff.f3_;
	f4_ = buff.f4_;
	t1_ = buff.t1_;
}
