#include "stock_data.h"
#include <cstring>
using namespace std;

binary_reader::stock_data::stock_data( std::ifstream& in )
{
	if(!in.read(reinterpret_cast<char*>(&stock_name_), 8) )
		return;
	if(!in.read(reinterpret_cast<char*>(&date_time_), 8) )
		return;
	if(!in.read(reinterpret_cast<char*>(&price_), sizeof(double)) )
		return;
	if(!in.read(reinterpret_cast<char*>(&vwap_), sizeof(double)) )
		return;
	if(!in.read(reinterpret_cast<char*>(&volume_), sizeof(boost::uint32_t)) )
		return;
	if(!in.read(reinterpret_cast<char*>(&f1_), sizeof(double))) 
		return;
	if(!in.read(reinterpret_cast<char*>(&t1_), sizeof(double)) )
		return;
	if(!in.read(reinterpret_cast<char*>(&f2_), sizeof(double)) )
		return;
	if(!in.read(reinterpret_cast<char*>(&f3_), sizeof(double)) )
		return;
	if(!in.read(reinterpret_cast<char*>(&f4_), sizeof(double)))
		return;
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
	memcpy( stock_name_, stock_name, 8);
	memcpy( date_time_, date_time, 8);
 	price_ = price;
	vwap_ = vwap;
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
void binary_reader::stock_data::write( std::ofstream& out ) const
{
	if(!out.write(stock_name_, 9) )
		throw logic_error("can't write");

	const char* date= date_time_;
  	int year_, month_, day_;
	sscanf_s( date_time_, "%4d%2d%2d", &year_, &month_, &day_ );
	boost::uint32_t date_ = 372*(year_-1) + 31*(month_-1) + day_;

	if(!out.write(reinterpret_cast< const char*>(&date_), sizeof( boost:: uint32_t)) )
		throw logic_error("can't write 'date'");
	if(!out.write(reinterpret_cast<const char*>(&vwap_), sizeof( double)) )
		throw logic_error("can't write 'vwap'");
	if(!out.write(reinterpret_cast<const char*>(&volume_), sizeof(boost:: uint32_t)) )
		throw logic_error("can't write 'volume'");
	if(!out.write(reinterpret_cast<const char*>(&f2_), sizeof( double)) )
		throw logic_error("can't write 'f2'");
}
void binary_reader::stock_data::write_raw( std::ofstream& out )
{	
	// your code. Can be emty
	// this method is used for testing. It writes data to the binary file without convertion.
}