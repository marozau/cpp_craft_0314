#include <cstring>
#include <stdexcept>

#include "market_message.h"

namespace binary_reader
{
	const std::logic_error unexpected_end_error( "unexpected error in data file" );

	market_message::market_message( std::ifstream& in ):
		type_( 0 ),
		time_( 0 ),
		len_( 0 ),
		msg_( NULL ),
		eof_( false )
	{
		binary_read( in, type_ );

		if( in.eof() )
		{
			// we are at the end of the stream
			eof_ = true;
			return;
		}

		binary_read( in, time_ );
		binary_read( in, len_ );

		//and now eof is unexpected situation
		if( in.eof() )
		{
			throw unexpected_end_error;
		}

		msg_ = new char[ len_ + 1 ];
		msg_[ len_ ] = '\0';

		if( len_ > 0 )
		{
			in.read( msg_, len_ );

			if( in.eof() )
			{
				throw unexpected_end_error;
			}
		}
	}

	market_message::market_message( const boost::uint32_t type,
									const boost::uint32_t time,
									const char* const msg ):
									type_( type ),
									time_( time ),
									eof_( false )
	{
		len_ = static_cast<uint32_t>( strlen( msg ) );
		msg_ = new char[ len_ + 1 ];
		strncpy( msg_, msg, len_ );
		msg_[ len_ ] = '\0';
	}

	void market_message::write( std::ofstream& out ) const
	{
		binary_write( out, type_ );
		binary_write( out, time_ );
		binary_write( out, len_ );

		out.write( msg_, len_ );
	}

	market_message::~market_message()
	{
		if( msg_ != NULL )
		{
			delete[] msg_;
		}
	}

	boost::uint32_t market_message::type() const
	{
		return type_;
	}
	boost::uint32_t market_message::time() const
	{
		return time_;
	}
	const char* const market_message::msg() const
	{
		return msg_;
	}

	bool market_message::eof() const
	{
		return eof_;
	}

	size_t market_message::size() const
	{
		return sizeof(type_) + 
			   sizeof(time_) + 
			   sizeof(len_) + 
			   len_;
	}
}