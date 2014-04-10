#include "test_registrator.h"

#include <message_reader.h>

#include <boost/filesystem.hpp>

void task4_4::tests_::message_reader_constructor_tests()
{
	BOOST_CHECK_THROW( message_reader mr( SOURCE_DIR "/no_such_file" ), std::logic_error );
	std::ofstream out( BINARY_DIR "/file.out" );
	out.close();

	BOOST_CHECK_NO_THROW( message_reader mr( BINARY_DIR "/file.out" ) );

	boost::filesystem::remove( BINARY_DIR "/file.out" );
}

void task4_4::tests_::message_reader_read_file_tests()
{
	{
		std::ofstream out( BINARY_DIR "/file.out" );
		out << "C";
		out.close();

		message_reader mr( BINARY_DIR "/file.out" );
		BOOST_CHECK_THROW( mr.read_file(), std::logic_error );
	}
	{
		std::ofstream out( BINARY_DIR "/file.out" );
		out << "A0123456789123456B10 0123456789";
		out.close();

		message_reader mr( BINARY_DIR "/file.out" );
		BOOST_CHECK_NO_THROW( mr.read_file() );
	}

	boost::filesystem::remove( BINARY_DIR "/file.out" );
}
