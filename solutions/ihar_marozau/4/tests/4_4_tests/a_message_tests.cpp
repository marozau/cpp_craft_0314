#include "test_registrator.h"

#include <iostream>
#include <stdexcept>

#include <a_message.h>


void task4_4::tests_::a_message_constructor_tests()
{
	std::stringstream test_stream;

	BOOST_CHECK_THROW( a_message::create_message( test_stream ), std::logic_error );
	test_stream.clear();

	test_stream << "0123456789123456";
	BOOST_CHECK_NO_THROW( a_message::create_message( test_stream ) );

	test_stream << "0123456789123456";
	message_ptr message = a_message::create_message( test_stream );
	
	BOOST_CHECK_EQUAL( message->type(), 'A' );
	BOOST_CHECK_EQUAL( message->str(), "a_message(0123456789123456)" );
}

