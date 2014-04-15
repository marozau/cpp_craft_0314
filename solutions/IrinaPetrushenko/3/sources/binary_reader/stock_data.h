#ifndef _BINARY_READER_STOCK_DATA_H_
#define _BINARY_READER_STOCK_DATA_H_

#include <fstream>

#include <boost/noncopyable.hpp>
#include <boost/cstdint.hpp>

namespace binary_reader
{
	class stock_data : virtual protected boost::noncopyable
	{
	public:
		const static size_t len_ = 8;
		char stock_name_[len_];
		char date_time_[len_];
		mutable double price_;
		mutable double vwap_;
		mutable boost::uint32_t volume_;
		mutable double f1_;
		mutable double t1_;
		mutable double f2_;
		mutable double f3_;
		mutable double f4_;

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
		void write( std::ofstream& out ) const;	
		void write_stock_name (std::ofstream& out) const; 
		void write_data (std::ofstream& out) const;
		void write_price (std::ofstream& out) const ;
		void write_volume (std::ofstream& out) const;
		void write_f2 (std::ofstream& out) const;

		const char * stock_name () const;

	//	const char *  stock_name () const;
	};
}

#endif // _BINARY_READER_STOCK_DATA_H_

