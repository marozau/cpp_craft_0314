#ifndef _BINARY_READER_MARKET_MESSAGE_H_
#define _BINARY_READER_MARKET_MESSAGE_H_

#include <fstream>

#include <boost/noncopyable.hpp>
#include <boost/cstdint.hpp>

namespace binary_reader
{
	template<class T>
	void binary_write( std::ostream& out, const T &t, size_t len = sizeof( T ) )
	{
		out.write( reinterpret_cast<const char*>( &t ), len );
	};

	template<class T>
	void binary_read( std::istream& in, T &t, size_t len = sizeof( T ) )
	{
		in.read( reinterpret_cast<char*>( &t ), len );
	};

	class market_message: virtual protected boost::noncopyable
	{
		boost::uint32_t type_;
		boost::uint32_t time_;
		boost::uint32_t len_;
		char* msg_;
		bool eof_;

	public:
		explicit market_message( std::ifstream& in );
		explicit market_message( const boost::uint32_t type, const boost::uint32_t time, const char* const msg );
		~market_message();
		//
		void write( std::ofstream& out ) const;

		boost::uint32_t type() const;
		boost::uint32_t time() const;
		const char* const msg() const;
		bool eof() const;

		size_t size() const;
	};
}

#endif // _BINARY_READER_MARKET_MESSAGE_H_
