#include "stock_data.h"
#include <iostream>
#include <exception>

using namespace std;

binary_reader::stock_data::stock_data( binary_reader:: binR& in )   
{
	if(!in.in.read(stock_name_, len_)) 
			in.error=1;
	if(!in.in.read(date_time_, len_))
			in.error=1;
	if(!in.in.read(reinterpret_cast<char*>(&price_), sizeof( double)) )
			in.error=1;
	if(!in.in.read(reinterpret_cast<char*>(&vwap_), sizeof( double)) )
			in.error=1;
	if(!in.in.read(reinterpret_cast<char*>(&volume_), sizeof( boost:: uint32_t)) )
			in.error=1;
	if(!in.in.read(reinterpret_cast<char*>(&f1_), sizeof( double))) 
			in.error=1;
	if(!in.in.read(reinterpret_cast<char*>(&t1_), sizeof( double)) )
			in.error=1;
	if(!in.in.read(reinterpret_cast<char*>(&f2_), sizeof( double)) )
			in.error=1;
	if(!in.in.read(reinterpret_cast<char*>(&f3_), sizeof( double)) )
			in.error=1;
	if(!in.in.read(reinterpret_cast<char*>(&f4_), sizeof( double)))
			in.error=1;
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
							const double f4 ) : price_(price), 
												vwap_(vwap), 
												volume_(volume), 
												f1_(f1), 
												t1_(t1),
												f2_(f2),
												f3_(f3),
												f4_(f4)
{
	memcpy( stock_name_, stock_name, len_);
	memcpy( date_time_, date_time, len_);
}
binary_reader::stock_data::~stock_data()
{
}

boost:: uint32_t binary_reader:: stock_data:: days( const char* const& date_time) const
{
	unsigned int day, month, year;
	sscanf( date_time, "%4d%2d%2d", &year,&month,&day);
	unsigned int  a=( (year-1)*372 + (month-1)*31 + day);
	return a;
}

void binary_reader::stock_data::write( binary_reader::binW& out ) const
{
	if(!out.out.write(stock_name_, len_+1) )
				throw logic_error("can't write stock_name_");
	const char* date= date_time_;
	const boost:: uint32_t a= days(date);
	if(!out.out.write(reinterpret_cast< const char*>(&a), sizeof( boost:: uint32_t)) )
				throw logic_error("can't write");
	if(!out.out.write(reinterpret_cast<const char*>(&vwap_), sizeof( double)) )
				throw logic_error("can't write");
	if(!out.out.write(reinterpret_cast<const char*>(&volume_), sizeof( boost:: uint32_t)) )
				throw logic_error("can't write");
	if(!out.out.write(reinterpret_cast<const char*>(&f2_), sizeof( double)) )
				throw logic_error("can't write");

}
void binary_reader::stock_data::write_raw( std::ofstream& out ) const
{	
	// your code. Can be emty
	// this method is used for testing. It writes data to the binary file without convertion.
}

const char* binary_reader::stock_data:: get_stock_name() const
{
	return stock_name_;
};


