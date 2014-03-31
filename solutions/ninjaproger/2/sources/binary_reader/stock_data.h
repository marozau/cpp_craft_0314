#ifndef _BINARY_READER_STOCK_DATA_H_
#define _BINARY_READER_STOCK_DATA_H_

#include <fstream>

#include <boost/noncopyable.hpp>
#include <boost/cstdint.hpp>

namespace binary_reader
{
	class stock_data : virtual protected boost::noncopyable
	{
		char _stock_name[8];
		char _date_time[8];
		double _price;
		double _vwap;
		boost::uint32_t _volume;
		double _f1;
		double _t1;
		double _f2;
		double _f3;
		double _f4;

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
		~stock_data();
		//
		void write( std::ofstream& out ) const;
		void write_raw( std::ofstream& out ) const;
	};
}

#endif // _BINARY_READER_STOCK_DATA_H_

