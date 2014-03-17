#ifndef _BINARY_READER_MARKET_MESSAGE_H_
#define _BINARY_READER_MARKET_MESSAGE_H_

#include <fstream>
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
		explicit market_message( std::ifstream& in );
		explicit market_message( const boost::uint32_t type=0u, const boost::uint32_t time=0u, const char* const msg=NULL );
		market_message( const market_message & a );
		market_message & operator = (const market_message & a);
		
	
		void write( std::ofstream& out );
		~market_message();

		size_t type() const;
		size_t time() const;
		boost::uint32_t len() const;
		const char* const msg() const;

		size_t size() const;
	};
}

#endif // _BINARY_READER_MARKET_MESSAGE_H_
