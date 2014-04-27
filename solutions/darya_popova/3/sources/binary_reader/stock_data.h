#ifndef _BINARY_READER_STOCK_DATA_H_
#define _BINARY_READER_STOCK_DATA_H_

#include <fstream>
#include <string>
#include <algorithm>
#include <boost/noncopyable.hpp>
#include <string>
#include <boost/cstdint.hpp>
#include "market_message.h"

namespace binary_reader
{
	class stock_data 
	{
		static const int len_= 8;
		char stock_name_[len_];
		char date_time_[len_];
		double price_;
		double vwap_;
		boost::uint32_t volume_;
		double f1_;
		double t1_;
		double f2_;
		double f3_;
		double f4_;
	
		boost:: uint32_t days( const char* const& date_time) const;

	public:

		explicit stock_data(binary_reader:: binR&  );
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
		void write( binary_reader:: binW& ) const;
		void write_raw( std::ofstream& out ) const;
		const char* get_stock_name() const;
		
	};
}

#endif //_BINARY_READER_STOCK_DATA_H_

