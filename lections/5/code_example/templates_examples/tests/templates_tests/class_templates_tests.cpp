#include "test_registrator.h"

#include <vector>
#include <string>

#include <class_templates.h>

void templates::tests_::vector_tests()
{
	BOOST_CHECK_NO_THROW( vector< std::string >() );
	vector< std::string > my_vector;

	BOOST_CHECK_THROW( my_vector.at( 0 ), std::out_of_range );

	BOOST_CHECK_NO_THROW( my_vector.push_back( "hello world" ) );

	BOOST_CHECK_EQUAL( my_vector[ 0 ], "hello world" );

	for ( size_t i = 0 ; i < 1023 ; ++i )
		BOOST_CHECK_NO_THROW( my_vector.push_back( "hello world" ) );

	BOOST_CHECK_THROW( my_vector.push_back( "buffer ended" ), std::out_of_range );
}

void templates::tests_::stack_tests()
{
	stack< int, 6 > int_stack;
	stack< std::string, 10240 > string_stack;

	BOOST_CHECK_NO_THROW( string_stack.push_back( "my string" ) );
	BOOST_CHECK_NO_THROW( string_stack.push_back( "my string2" ) );
	BOOST_CHECK_NO_THROW( BOOST_CHECK_EQUAL( string_stack.pop(), "my string2" ) );
	BOOST_CHECK_NO_THROW( BOOST_CHECK_EQUAL( string_stack.pop(), "my string" ) );
	BOOST_CHECK_THROW( string_stack.pop(), std::out_of_range );

	for (size_t i = 0 ; i < 10240 ; ++i )
	{
		BOOST_CHECK_NO_THROW( string_stack.push_back( "hello world" ) );
	}
	BOOST_CHECK_THROW( string_stack.push_back( "hello world" ), std::out_of_range );

	//
	//
	std::vector< int > int_v( 5, 3 );
	stack< int, 6 > int_stack_from_container( int_v );
	//
	//
	BOOST_CHECK_EQUAL( make_pair( 15, 16.0 ).first, 15 );
	BOOST_CHECK_EQUAL( make_pair( 15, 16.0 ).second, 16.0 );
}
