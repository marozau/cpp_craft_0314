#ifndef _BINARY_READER_MARKET_MESSAGE_H_
#define _BINARY_READER_MARKET_MESSAGE_H_

#include <fstream>
#include <map>
#include <boost/noncopyable.hpp>
#include <boost/cstdint.hpp>

namespace binary_reader
{
	class market_message 
	{

		boost::uint32_t type_;
		boost::uint32_t time_;
		boost::uint32_t len_;
		char* msg_;

	public:
		static const boost::uint32_t buffer_size = 2048; 

		explicit market_message( std::ifstream& );
		explicit market_message( const boost::uint32_t, const boost::uint32_t, const char* const );
		void write( std::ofstream& ) const;
		void write_txt( std::ofstream& ) const;
		~market_message();
		//
		boost::uint32_t type() const;
		boost::uint32_t time() const;
		boost::uint32_t len() const;
		bool check( boost:: uint32_t& ) const;
		const char* const msg() const;

		size_t get_size() const;
		bool check_size( std::map <boost::uint32_t, size_t>&) const;
	};
}

#endif // _BINARY_READER_MARKET_MESSAGE_H_
