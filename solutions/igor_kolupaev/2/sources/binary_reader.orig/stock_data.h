#ifndef _BINARY_READER_STOCK_DATA_H_
#define _BINARY_READER_STOCK_DATA_H_

#include <fstream>

#include <boost/noncopyable.hpp>
#include <boost/cstdint.hpp>

namespace binary_reader
{
	class stock_data: virtual protected boost::noncopyable
	{
		char stock_name_[ 8 ];
		char date_time_[ 8 ];
		double price_;
		double vwap_;
		boost::uint32_t volume_;
		double f1_;
		double t1_;
		double f2_;
		double f3_;
		double f4_;

		bool _eof;

		boost::uint32_t date_as_uint();

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
		const char* stock_name() { return stock_name_; }
		const char* date_time() { return date_time_; }
		double price() { return price_; }
		double vwap() { return vwap_; }
		boost::uint32_t volume() { return volume_; }
		double f1() { return f1_; }
		double t1() { return t1_; }
		double f2() { return f2_; }
		double f3() { return  f3_; }
		double f4() { return f4_; }

		//
		void write( std::ofstream& out );
		void write_raw( std::ofstream& out );

		bool eof()
		{
			return _eof;
		}
	};
}

#endif // _BINARY_READER_STOCK_DATA_H_

