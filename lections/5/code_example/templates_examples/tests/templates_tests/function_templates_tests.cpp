#include "test_registrator.h"

#include <vector>

#include <function_templates.h>

void templates::tests_::function_1_tests()
{
	function_1< int, double >( 15, 16.0 );


	BOOST_CHECK_EQUAL( ( function_1< int, double >( 15, 16.0 ) ), "15 16" );

	//function_1( 15, 16.0 ); 

	// uncomment me to get into troubles ( unresolved external symbol )

	 // function_1< int, float >( 15, 16.0 );
	// function_1( 15.0, 16.0 ); 
}

void templates::tests_::function_2_tests()
{
	// uncomment me to get into troubles ( template parameter 'T2' is ambiguous )
//	function_2( 15, 15.0, 18 );

	BOOST_CHECK_EQUAL( function_2( 15, 15.0, 18.0 ), "18" );
}

void templates::tests_::function_3_tests()
{
	BOOST_CHECK_EQUAL( function_3< int >( 28 ), 2 );
	BOOST_CHECK_EQUAL( function_3< double >( 28 ), 2.8 );
}

void templates::tests_::function_4_tests()
{
	BOOST_CHECK_EQUAL( function_4( 15 ), "t1_int" );
	BOOST_CHECK_EQUAL( function_4( 15.6 ), "t1_double" );
	BOOST_CHECK_EQUAL( function_4( "line" ), "casual" );
}

void templates::tests_::function_5_tests()
{
	BOOST_CHECK_EQUAL( function_5( std::vector< int >() ), "int" );
	BOOST_CHECK_EQUAL( function_5( std::vector< char >() ), "char" );
	BOOST_CHECK_EQUAL( function_5( std::string() ), "char" );
	BOOST_CHECK_EQUAL( function_5( int() ) , "unknown" );
}
