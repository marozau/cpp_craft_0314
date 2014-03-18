#include "stock_data.h"
#include <iostream>


binary_reader::stock_data::stock_data( std::ifstream& in )
{
	if(!in.read(stock_name_, 9)) 
	{
		std::cerr<<"Input is incorrect"<< std::endl;
		return;
	}
	if(!in.read(date_time_, 9))
	{
		std::cerr<<"Input is incorrect"<< std::endl;
		return;
	}
	if(!in.read(reinterpret_cast<char*>(&price_), sizeof( double)) )
	{
		std::cerr<<"Input is incorrect"<< std::endl;
		return;
	}
	if(!in.read(reinterpret_cast<char*>(&vwap_), sizeof( double)) )
	{
		std::cerr<<"Input is incorrect"<< std::endl;
		return;
	}
	if(!in.read(reinterpret_cast<char*>(&volume_), sizeof( boost:: uint32_t)) )
	{
		std::cerr<<"Input is incorrect"<< std::endl;
		return;
	}
	if(!in.read(reinterpret_cast<char*>(&f1_), sizeof( double))) 
	{
		std::cerr<<"Input is incorrect"<< std::endl;
		return;
	}
	if(!in.read(reinterpret_cast<char*>(&t1_), sizeof( double)) )
	{
		std::cerr<<"Input is incorrect"<< std::endl;
		return;
	}
	if(!in.read(reinterpret_cast<char*>(&f2_), sizeof( double)) )
	{
		std::cerr<<"Input is incorrect"<< std::endl;
		return;
	}
	if(!in.read(reinterpret_cast<char*>(&f3_), sizeof( double)) )
	{
		std::cerr<<"Input is incorrect"<< std::endl;
		return;
	}
	if(!in.read(reinterpret_cast<char*>(&f4_), sizeof( double)))
	{
		std::cerr<<"Input is incorrect"<< std::endl;
		return;
	}
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
	price_=price;
	vwap_=vwap;
	volume_=volume;
	f1_=f1;
	t1_=t1;
	f2_=f2;
	f3_=f3;
	f4_=f4;
 	// don't forget about initialization list
}
binary_reader::stock_data::~stock_data()
{
}

boost:: uint32_t binary_reader:: stock_data:: days( char*& date_time)
{
	unsigned int day, month, year;
	sscanf( date_time, "%4d%2d%2d", &year,&month,&day);
	unsigned int  a=( (year-1)*372 + (month-1)*31 + day);
	return a;
}

void binary_reader::stock_data::write( std::ofstream& out )
{
	if(!out.write(stock_name_, 9) )
	{
		std::cerr<<"Can't write"<< std::endl;
		return;
	}
	char* date= date_time_;
	boost:: uint32_t a= days(date);
	if(!out.write(reinterpret_cast<char*>(&a), sizeof( boost:: uint32_t)) )
	{
		std::cerr<<"Can't write"<< std::endl;
		return;
	}
	if(!out.write(reinterpret_cast<char*>(&vwap_), sizeof( double)) )
	{
		std::cerr<<"Can't write"<< std::endl;
		return;
	}
	if(!out.write(reinterpret_cast<char*>(&volume_), sizeof( boost:: uint32_t)) )
	{
		std::cerr<<"Can't write"<< std::endl;
		return;
	}
	if(!out.write(reinterpret_cast<char*>(&f2_), sizeof( double)) )
	{
		std::cerr<<"Can't write"<< std::endl;
		return;
	}

}
void binary_reader::stock_data::write_raw( std::ofstream& out )
{	
	// your code. Can be emty
	// this method is used for testing. It writes data to the binary file without convertion.
}



