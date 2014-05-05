#include "test_registrator.h"

#include <stdexcept>

#include <b_message.h>


void task4_4::tests_::b_message_constructor_tests()
{
	std::stringstream test_stream;

	BOOST_CHECK_THROW( b_message::create_message( test_stream ), std::logic_error );
	test_stream.clear();

	test_stream << "16 01234567891234";
	BOOST_CHECK_THROW( b_message::create_message( test_stream ), std::logic_error );

	test_stream.clear();
	test_stream << "16 0123456789123456";
	BOOST_CHECK_NO_THROW( b_message::create_message( test_stream ) );
	
	test_stream.clear();
	test_stream << "16 0123456789123456";
	message_ptr message = b_message::create_message( test_stream );

	BOOST_CHECK_EQUAL( message->type(), 'B' );
	BOOST_CHECK_EQUAL( message->str(), "b_message(16|0123456789123456)" );
}

