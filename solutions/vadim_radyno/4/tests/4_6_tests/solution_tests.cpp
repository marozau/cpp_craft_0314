#include "test_registrator.h"

#include <iostream>
#include <limits>
#include <stdexcept>

#include <solution.h>

void task4_6::tests_::solution_constructor_tests()
{
	task4_6::lines lines;

	BOOST_CHECK_NO_THROW( solution s( lines ) );

	{
		lines.push_back( "A = 5 + ( 45 - 54 * 23 ) * C ");
		BOOST_CHECK_THROW( solution s( lines ), std::logic_error );
		lines.clear();
	}
	{
		lines.push_back( "A = 5 + ( 45 - 54 * 23 )");
		lines.push_back( "B = 15 / 23 )");
		BOOST_CHECK_THROW( solution s( lines ), std::logic_error );
		lines.clear();
	}
	{
		lines.push_back( "A = 5 + ( 45 - 54 * 23 )");
		lines.push_back( "B = 15 / 15");
		lines.push_back( "C = A + B");
		lines.push_back( "C = 45 + 65");
		BOOST_CHECK_THROW( solution s( lines ), std::logic_error );
		lines.clear();
	}
	{
		lines.push_back( "A = 56 / 0 ");
		BOOST_CHECK_THROW( solution s( lines ), std::logic_error );
		lines.clear();
	}
	{
		lines.push_back( "A = 45 + + 76");
		BOOST_CHECK_THROW( solution s( lines ), std::logic_error );
		lines.clear();
	}
}

void task4_6::tests_::solution_results_tests()
{
	task4_6::lines lines;
	
	lines.push_back( "A = 5 + ( 45 - 54 * 23 ) * 87 ");
	lines.push_back( "B = 43 ");
	lines.push_back( "C = B + 90 - 3 ");
	lines.push_back( "D = B + 0.1 * C");
	lines.push_back( "E = B * 0.1");
	lines.push_back( "F = (B + 4) * 0.1");

	BOOST_CHECK_NO_THROW( solution s( lines ) );

	solution s( lines );

	BOOST_CHECK_EQUAL( s.result_for( "A" ), -104134 );
	BOOST_CHECK_EQUAL( s.result_for( "B" ), 43 );
	BOOST_CHECK_EQUAL( s.result_for( "C" ), 130 );
	BOOST_CHECK_EQUAL( s.result_for( "E" ), 4 );
	BOOST_CHECK_EQUAL( s.result_for( "F" ), 5 );
}
