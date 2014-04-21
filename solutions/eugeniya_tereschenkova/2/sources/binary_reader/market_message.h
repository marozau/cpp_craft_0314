#ifndef _BINARY_READER_MARKET_MESSAGE_H_
#define _BINARY_READER_MARKET_MESSAGE_H_

#include <fstream>
#include <math.h>

#include <boost/noncopyable.hpp>
#include <boost/cstdint.hpp>

namespace binary_reader
{
	class market_message : virtual protected boost::noncopyable
	{
		boost::uint32_t type_;
		boost::uint32_t time_;
		boost::uint32_t len_;
		char* msg_;

	public:
		explicit market_message( std::ifstream& in );
		explicit market_message( const boost::uint32_t type, const boost::uint32_t time, const char* const msg );
		void write( std::ofstream& out );
		~market_message();
		//
		bool check_time(boost:: uint32_t& cur_time) const;
		boost::uint32_t type() const;
		boost::uint32_t time() const;
		const char* const msg() const;
	};
}

#endif // _BINARY_READER_MARKET_MESSAGE_H_