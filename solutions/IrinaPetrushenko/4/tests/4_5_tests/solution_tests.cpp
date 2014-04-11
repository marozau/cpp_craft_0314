#include "test_registrator.h"

#include <iostream>
#include <limits>

#include <solution.h>

void task4_5::tests_::solution_simple_tests()
{
	task4_5::data_type data;

	BOOST_CHECK_NO_THROW( solution s( data ) );
	solution s( data );
	BOOST_CHECK_EQUAL( s.get_min(), 0 );
	BOOST_CHECK_EQUAL( s.get_max(), 0 );
}

void task4_5::tests_::solution_full_random_tests()
{
	task4_5::data_type data;

	int min = std::numeric_limits< int >().max();
	int max = std::numeric_limits< int >().min();

	for ( size_t i = 0 ; i < 4 ; ++i )
	{
		data.push_back( task4_5::data_type::value_type() );
		for ( size_t u = 0 ; u < 1000000 ; ++u )
		{
			const int new_element = ( rand() % 200000000 ) * ( rand() % 2 - 2 ) ;
			min = std::min( min, new_element );
			max = std::max( max, new_element );
			data[i].push_back( new_element );
		}
	}

	solution s( data );
	BOOST_CHECK_EQUAL( s.get_min(), min );
	BOOST_CHECK_EQUAL( s.get_max(), max );
		
}

void task4_5::tests_::solution_partially_random_tests()
{
	task4_5::data_type data;

	int min = std::numeric_limits< int >().max();
	int max = std::numeric_limits< int >().min();

	for ( size_t i = 0 ; i < 20 ; ++i )
	{
		data.push_back( task4_5::data_type::value_type() );

		for ( size_t u = 0 ; u < rand() ; ++u )
		{
			const int new_element = rand() % 200000000;
			min = std::min( min, new_element );
			max = std::max( max, new_element );
			data[i].push_back( new_element );
		}
		{
			const int new_element = 400001;
			min = std::min( min, new_element );
			max = std::max( max, new_element );
			data[i].push_back( new_element );
		}
		for ( size_t u = 0 ; u < rand() ; ++u )
		{
			const int new_element = rand() % 200000000;
			min = std::min( min, new_element );
			max = std::max( max, new_element );
			data[i].push_back( new_element );
		}

	}

	solution s( data );
	BOOST_CHECK_EQUAL( s.get_min(), min );
	BOOST_CHECK_EQUAL( s.get_max(), max );
		
}

