#ifndef _BINARY_READER_STOCK_DATA_H_
#define _BINARY_READER_STOCK_DATA_H_

#include <fstream>

#include <boost/cstdint.hpp>

namespace binary_reader
{
	class stock_data
	{
		char *stock_name_;
		const static size_t stock_size = sizeof( char )*8;
		char *date_time_;
		const static size_t date_size = sizeof( char )*8;
		double price_;
		double vwap_;
		boost::uint32_t volume_;
		double f1_;
		double t1_;
		double f2_;
		double f3_;
		double f4_;

	public:
		explicit stock_data( std::ifstream& in );
		explicit stock_data( const char* stock_name,
							const char* date_time,
							const double price,
							const double vwap,
							const boost::uint32_t volume,
							const double f1,
							const double t1,
							const double f2,
							const double f3,
							const double f4 );	
		explicit stock_data( const stock_data& buff );
		~stock_data();
		//
		void write( std::ofstream& out );
		char* stock_name();
	};
}

#endif // _BINARY_READER_STOCK_DATA_H_

