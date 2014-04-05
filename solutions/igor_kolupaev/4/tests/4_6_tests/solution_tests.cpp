#include "test_registrator.h"

#include <iostream>
#include <limits>
#include <stdexcept>

#include "solution.h"
#include "infix_reader.h"

void task4_6::tests_::infix_reader_tests()
{
	{
		expression_calc::infix_reader reader( std::string( "-0.1" ) );
		std::string s;

		reader.read( s );
		BOOST_CHECK_EQUAL( s, "-0.1" );
	}

	{
		expression_calc::infix_reader reader( std::string( "++" ) );
		std::string s;

		reader.read( s );
		BOOST_CHECK_EQUAL( s, "+" );
		
		reader.read( s );
		BOOST_CHECK_EQUAL( s, "+" );

		BOOST_CHECK_EQUAL( reader.eof(), true );
	}

	task4_6::lines lines;

	expression_calc::infix_reader reader( std::string( "F = ( B + 4 ) * 0.1" ) );
	expression_calc::infix_reader reader1( std::string( "F=(B+4)*0.1" ) );
	while( !reader.eof() && !reader1.eof() )
	{
		std::string s;
		reader.read( s );
		lines.push_back( s );

		reader1.read( s );
		BOOST_CHECK_EQUAL( lines.back(), s );
	}

	BOOST_CHECK_EQUAL( lines[ 0 ].c_str(), "F" );
	BOOST_CHECK_EQUAL( lines[ 1 ].c_str(), "=" );
	BOOST_CHECK_EQUAL( lines[ 2 ].c_str(), "(" );
	BOOST_CHECK_EQUAL( lines[ 3 ].c_str(), "B" );
	BOOST_CHECK_EQUAL( lines[ 4 ].c_str(), "+" );
	BOOST_CHECK_EQUAL( lines[ 5 ].c_str(), "4" );
	BOOST_CHECK_EQUAL( lines[ 6 ].c_str(), ")" );
	BOOST_CHECK_EQUAL( lines[ 7 ].c_str(), "*" );
	BOOST_CHECK_EQUAL( lines[ 8 ].c_str(), "0.1" );
}


void task4_6::tests_::solution_develop_tests()
{
	task4_6::lines lines;

	{
		lines.push_back( "F = ( 43 + 4 ) * 0.1" );
		solution s( lines );
		BOOST_CHECK_EQUAL( s.result_for( "F" ), 5 );
		lines.clear();
	}

	{
		lines.push_back( "A = 1 + 1" );
		solution s( lines );
		BOOST_CHECK_EQUAL( s.result_for( "A" ), 2 );
		lines.clear();
	}

	{
		lines.push_back( "1 + 1" );
		solution s( lines );
		BOOST_CHECK_EQUAL( s.result_for( "result" ), 2 );
		lines.clear();
	}

	{
		lines.push_back( "1 * 1" );
		solution s( lines );
		BOOST_CHECK_EQUAL( s.result_for( "result" ), 1 );
		lines.clear();
	}

	{
		lines.push_back( "1 / 1" );
		solution s( lines );
		BOOST_CHECK_EQUAL( s.result_for( "result" ), 1 );
		lines.clear();
	}

	{
		lines.push_back( "1 - 1" );
		solution s( lines );
		BOOST_CHECK_EQUAL( s.result_for( "result" ), 0 );
		lines.clear();
	}
}

void task4_6::tests_::solution_constructor_tests()
{
	task4_6::lines lines;

	BOOST_CHECK_NO_THROW( solution s( lines ) );

	{
		lines.push_back( "A = 5 + ( 45 - 54 * 23 ) * C " );
		BOOST_CHECK_THROW( solution s( lines ), std::logic_error );
		lines.clear();
	}
	{
		lines.push_back( "A = 5 + ( 45 - 54 * 23 )" );
		lines.push_back( "B = 15 / 23 )" );
		BOOST_CHECK_THROW( solution s( lines ), std::logic_error );
		lines.clear();
	}
	{
		lines.push_back( "A = 5 + ( 45 - 54 * 23 )" );
		lines.push_back( "B = 15 / 15" );
		lines.push_back( "C = A + B" );
		lines.push_back( "C = 45 + 65" );
		BOOST_CHECK_THROW( solution s( lines ), std::logic_error );
		lines.clear();
	}
	{
		lines.push_back( "A = 56 / 0 " );
		BOOST_CHECK_THROW( solution s( lines ), std::logic_error );
		lines.clear();
	}
	{
		lines.push_back( "A = 45 + + 76" );
		BOOST_CHECK_THROW( solution s( lines ), std::logic_error );
		lines.clear();
	}
}

void task4_6::tests_::solution_results_tests()
{
	task4_6::lines lines;

	lines.push_back( "A = 5 + ( 45 - 54 * 23 ) * 87 " );
	lines.push_back( "B = 43 " );
	lines.push_back( "C = B + 90 - 3 " );
	lines.push_back( "D = B + 0.1 * C" );
	lines.push_back( "E = B * 0.1" );
	lines.push_back( "F = (B + 4) * 0.1" );

	BOOST_CHECK_NO_THROW( solution s( lines ) );

	solution s( lines );

	BOOST_CHECK_EQUAL( s.result_for( "A" ), -104134 );
	BOOST_CHECK_EQUAL( s.result_for( "B" ), 43 );
	BOOST_CHECK_EQUAL( s.result_for( "C" ), 130 );
	BOOST_CHECK_EQUAL( s.result_for( "E" ), 4 );
	BOOST_CHECK_EQUAL( s.result_for( "F" ), 5 );
}
