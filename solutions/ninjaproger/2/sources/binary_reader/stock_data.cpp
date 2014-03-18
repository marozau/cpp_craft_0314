#include "stock_data.h"

binary_reader::stock_data::stock_data( std::ifstream& in )
{
	// your code
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
	// your code
 	// don't forget about initialization list
}
binary_reader::stock_data::~stock_data()
{
	// your code
}
void binary_reader::stock_data::write( std::ofstream& out )
{
	// your code
}
void binary_reader::stock_data::write_raw( std::ofstream& out )
{	
	// your code. Can be emty
	// this method is used for testing. It writes data to the binary file without convertion.
}
