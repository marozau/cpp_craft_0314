#include <cstring>
#include <stdexcept>

#include "market_message.h"

namespace binary_reader
{
	union unit32_dto
	{
		char char_value[ 4 ];
		boost::uint32_t uint_value;
	};

	const std::logic_error unexpected_end_error( "unexpected error in data file" );

	boost::uint32_t read_uint( std::ifstream& in )
	{
		unit32_dto dto;

		in.read( dto.char_value, sizeof( dto.uint_value ) );

		return dto.uint_value;
	};

	void write_uint( std::ofstream& out, uint32_t v )
	{
		unit32_dto dto;
		dto.uint_value = v;

		out.write( dto.char_value, sizeof( dto.uint_value ) );
	};

	market_message::market_message( std::ifstream& in ):
		type_( 0 ),
		time_( 0 ),
		len_( 0 ),
		msg_( NULL ),
		eof_( false )
	{
		type_ = read_uint( in );

		if( in.eof() )
		{
			// we are at the end of the stream
			eof_ = true;
			return;
		}

		time_ = read_uint( in );
		len_ = read_uint( in );

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

	void market_message::write( std::ofstream& out )
	{
		write_uint( out, type_ );
		write_uint( out, time_ );
		write_uint( out, len_ );
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
}