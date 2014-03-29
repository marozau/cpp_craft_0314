#include "test_registrator.h"
#include "market_message.h"

#include <boost/filesystem.hpp>

namespace binary_reader
{
	namespace tests_
	{
		namespace detail
		{
			std::string generate_string( const size_t len = 20 );
		}
	}
}

std::string binary_reader::tests_::detail::generate_string( const size_t len )
{
	std::string res;
	for ( size_t i = 0 ; i < len ; ++i )
		res += rand() % ( 'z' - 'a' ) + 'a';
	return res;
}

void binary_reader::tests_::test_market_message()
{
	static const std::string test_file_name = BINARY_DIR "/test_out.txt";
	BOOST_CHECK_NO_THROW( market_message( 1, 2, "hello world" ) );
	{
		std::ofstream out( test_file_name.c_str(), std::ios_base::binary );
		market_message mm( 1ul,2ul, "hello world" );
		mm.write( out );
	}
	{
		std::ifstream in( test_file_name.c_str(), std::ios_base::binary );
		market_message mm( in );
		BOOST_CHECK_EQUAL( mm.type(), 1ul );
		BOOST_CHECK_EQUAL( mm.time(), 2ul );
		BOOST_CHECK_EQUAL( memcmp( mm.msg(), "hello world", 10ul ), 0 );
	}
	{
		std::ofstream out( test_file_name.c_str(), std::ios_base::binary );
		market_message mm( 1ul,2ul, "hello world" );
		mm.write( out );
	}
	{
		std::ofstream out( test_file_name.c_str(), std::ios_base::binary );
		for( boost::uint32_t i = 0 ; i < 100000 ; ++i )
		{
			const std::string string = "1234";
			market_message mm( 1ul, i , string.c_str() );
			mm.write( out );
		}
	}
	{
		std::ifstream in( test_file_name.c_str(), std::ios_base::binary );
		size_t amount = 0;
		while ( !in.eof() )
		{
			++amount;
			market_message mm( in );
		}
		BOOST_CHECK_EQUAL( amount, 100001ul );
	}
	boost::filesystem::remove( test_file_name );
}

void binary_reader::tests_::generate_2_4_tests()
{
	{
		std::ofstream out( BINARY_DIR "/input_241.txt", std::ios_base::binary );
		market_message( 1ul,2ul, detail::generate_string().c_str() ).write( out );
		market_message( 1ul,1ul, detail::generate_string().c_str() ).write( out );
		market_message( 5ul,1ul, detail::generate_string().c_str() ).write( out );
		market_message( 3ul,1ul, detail::generate_string().c_str() ).write( out );
		market_message( 3ul,5ul, detail::generate_string().c_str() ).write( out );
		market_message( 3ul,2ul, detail::generate_string().c_str() ).write( out );
		market_message( 3ul,3ul, detail::generate_string().c_str() ).write( out );
		market_message( 3ul,4ul, detail::generate_string().c_str() ).write( out );
		market_message( 3ul,5ul, detail::generate_string().c_str() ).write( out );
	}
	{
		std::ofstream out( BINARY_DIR "/input_242.txt", std::ios_base::binary );
		for ( boost::uint32_t i = 0 ; i < 100000 ; ++i )
		{
			market_message( 1ul,i, detail::generate_string( 0 ).c_str() ).write( out );
			market_message( 3ul,i, detail::generate_string( 0 ).c_str() ).write( out );
		}
	}
	{
		std::ofstream out( BINARY_DIR "/input_243.txt", std::ios_base::binary );
		for ( boost::uint32_t i = 0 ; i < 100000 ; ++i )
		{
			market_message( 1ul,i, detail::generate_string( ).c_str() ).write( out );
			market_message( 3ul,i, detail::generate_string( ).c_str() ).write( out );
		}
	}
}
void binary_reader::tests_::generate_2_5_tests()
{
	{
		std::ofstream out( BINARY_DIR "/input_251.txt", std::ios_base::binary );
		market_message( 1ul,1ul, detail::generate_string().c_str() ).write( out );
		market_message( 2ul,1ul, detail::generate_string().c_str() ).write( out );
		market_message( 3ul,1ul, detail::generate_string().c_str() ).write( out );
		market_message( 4ul,1ul, detail::generate_string().c_str() ).write( out );
		market_message( 5ul,1ul, detail::generate_string().c_str() ).write( out );
		market_message( 1ul,2ul, detail::generate_string().c_str() ).write( out );
		market_message( 2ul,2ul, detail::generate_string().c_str() ).write( out );
		market_message( 3ul,2ul, detail::generate_string().c_str() ).write( out );
		market_message( 4ul,2ul, detail::generate_string().c_str() ).write( out );
		market_message( 5ul,2ul, detail::generate_string().c_str() ).write( out );
	}
	{
		std::ofstream out( BINARY_DIR "/input_252.txt", std::ios_base::binary );
		market_message( 1ul,1ul, detail::generate_string( 2048 ).c_str() ).write( out );
	}
	{
		std::ofstream out( BINARY_DIR "/input_253.txt", std::ios_base::binary );
		market_message( 1ul,1ul, detail::generate_string( 2020 ).c_str() ).write( out );
		market_message( 2ul,1ul, detail::generate_string( 2000 ).c_str() ).write( out );
		market_message( 1ul,1ul, detail::generate_string( 2020 ).c_str() ).write( out );
		market_message( 2ul,1ul, detail::generate_string( 20 ).c_str() ).write( out );
	}
}
