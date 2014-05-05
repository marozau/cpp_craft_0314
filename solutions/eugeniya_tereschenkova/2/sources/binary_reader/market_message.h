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
		static const boost::uint32_t buffer_size = 2048; 

		explicit market_message( std::ifstream& in );
		explicit market_message( const boost::uint32_t type, const boost::uint32_t time, const char* const msg );
		void write( std::ofstream& out ) const;
		~market_message();
		//
		const bool check_time(boost:: uint32_t& cur_time) const;
		const boost::uint32_t type() const;
		const boost::uint32_t time() const;
		const boost::uint32_t len() const;
		const char* const msg() const;
		const boost::uint32_t msg_size() const;
		const bool check_msg_size(const boost::uint32_t& cur_msg_size) const;
	};
}

#endif // _BINARY_READER_MARKET_MESSAGE_H_
