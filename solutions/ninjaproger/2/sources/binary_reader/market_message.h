#ifndef _BINARY_READER_MARKET_MESSAGE_H_
#define _BINARY_READER_MARKET_MESSAGE_H_

#include <fstream>

#include <boost/noncopyable.hpp>
#include <boost/cstdint.hpp>



namespace binary_reader
{
	class market_message : virtual protected boost::noncopyable
	{
		boost::uint32_t _type;
		boost::uint32_t _time;
		boost::uint32_t _len;
		char* _msg;
        
	public:
        enum types {MARKET_OPEN = 1,TRADE,QUOTE,MARKET_CLOSE};
		explicit market_message( std::ifstream& in );
		explicit market_message( const boost::uint32_t type, const boost::uint32_t time,const boost::uint32_t len,const char* const msg );
		void write( std::ofstream& out );
		~market_message();
		//
		boost::uint32_t type() const;
		boost::uint32_t time() const;
        boost::uint32_t msg_len() const;
		const char* const msg() const;
	};
}

#endif // _BINARY_READER_MARKET_MESSAGE_H_
