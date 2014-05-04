#include "test_registrator.h"

#include <vector.h>

#include <numeric>
#include <stdexcept>

void task5_5::tests_::vector_tests()
{
	{
		vector< int > int_vector;
		BOOST_CHECK_EQUAL( int_vector.size(), 0ul );
		BOOST_CHECK_EQUAL( int_vector.capacity(), 4ul ); // default capacity is 4ul
	}
	{
		vector< int > int_vector;
		BOOST_CHECK_EQUAL( int_vector.begin() == int_vector.end(), true );
	}
	{
		vector< int > int_vector;
		const vector< int >& ref = int_vector;
		BOOST_CHECK_EQUAL( ref.begin() == ref.end(), true );
	}
	{
		vector< int > iv;
		BOOST_CHECK_THROW( iv[ 0 ], std::out_of_range );
		BOOST_CHECK_THROW( iv[ 100 ], std::out_of_range );
		BOOST_CHECK_THROW( iv[ 1000 ], std::out_of_range );
		BOOST_CHECK_THROW( iv[ 10000 ], std::out_of_range );
	}
	{
		vector< int > iv;
		BOOST_CHECK_NO_THROW( iv.resize( 100ul ) );
		BOOST_CHECK_NO_THROW( iv[ 0 ] );
		BOOST_CHECK_NO_THROW( iv[ 99 ] );
		BOOST_CHECK_THROW( iv[ 100 ], std::out_of_range );
		BOOST_CHECK_THROW( iv[ 1000 ], std::out_of_range );
		BOOST_CHECK_THROW( iv[ 10000 ], std::out_of_range );
		BOOST_CHECK_EQUAL( iv.size(), 100ul );
		BOOST_CHECK_EQUAL( iv.capacity(), 100ul );
	}
	{ 
		vector< int > iv;
		vector< int > iv_copy;
		BOOST_CHECK_NO_THROW( iv_copy = iv );
	}
	{
		vector< int > iv;
		for( int i = 0; i < 10; ++i )
			iv.push_back( i );
		vector< int > iv_copy = iv;
		for( int i = 0; i < 10; ++i )
			BOOST_CHECK_EQUAL( iv[ i ], iv_copy[ i ] );
		BOOST_CHECK_EQUAL( iv_copy.size(), 10 );
		BOOST_CHECK_EQUAL( iv.capacity(), 16 );
		BOOST_CHECK_EQUAL( iv_copy.capacity(), 16 );

	}
	{ // this test will help you understand work of capacity on push_back
		vector< int > iv;
		BOOST_CHECK_EQUAL( iv.size(), 0ul );
		BOOST_CHECK_EQUAL( iv.capacity(), 4ul );
		iv.push_back( 45 );
		iv.push_back( 45 );
		BOOST_CHECK_EQUAL( iv.size(), 2ul );
		BOOST_CHECK_EQUAL( iv.capacity(), 4ul );
		iv.push_back( 45 );
		BOOST_CHECK_EQUAL( iv.size(), 3ul );
		BOOST_CHECK_EQUAL( iv.capacity(), 4ul );
		iv.push_back( 34 );
		BOOST_CHECK_EQUAL( iv.size(), 4ul );
		BOOST_CHECK_EQUAL( iv.capacity(), 4ul );
		iv.push_back( 87 );
		BOOST_CHECK_EQUAL( iv.size(), 5ul );
		BOOST_CHECK_EQUAL( iv.capacity(), 8ul );
		for ( size_t i = 0 ; i < 4 ; ++i )
			iv.push_back( 45 );
		BOOST_CHECK_EQUAL( iv.size(), 9ul );
		BOOST_CHECK_EQUAL( iv.capacity(), 16ul );
	}
	{
		vector< int > iv;
		BOOST_CHECK_EQUAL( iv.size(), 0ul );
		BOOST_CHECK_EQUAL( iv.capacity(), 4ul );
		iv.reserve( 7ul );
		BOOST_CHECK_EQUAL( iv.size(), 0ul );
		BOOST_CHECK_EQUAL( iv.capacity(), 7ul );
		for ( size_t i = 0 ; i < 8 ; ++i )
			iv.push_back( 23 );
		BOOST_CHECK_EQUAL( iv.size(), 8ul );
		BOOST_CHECK_EQUAL( iv.capacity(), 14ul );
		iv.reserve( 3ul );
		BOOST_CHECK_EQUAL( iv.size(), 8ul );
		BOOST_CHECK_EQUAL( iv.capacity(), 14ul );
	}
	{
		vector< int > iv;
		for ( size_t i = 0 ; i < 9 ; ++i )
			iv.push_back( 23 );
		iv.resize( 3 );
		BOOST_CHECK_EQUAL( iv.size(), 3ul );
		BOOST_CHECK_EQUAL( iv.capacity(), 16ul );
		BOOST_CHECK_THROW( iv[ 3 ], std::out_of_range );
		iv.resize( 19 );
		BOOST_CHECK_EQUAL( iv.size(), 19ul );
		BOOST_CHECK_EQUAL( iv.capacity(), 19ul );
		BOOST_CHECK_THROW( iv[ 19 ], std::out_of_range );
		iv.resize( 4 );
		BOOST_CHECK_EQUAL( iv.size(), 4ul );
		BOOST_CHECK_EQUAL( iv.capacity(), 19ul );
		BOOST_CHECK_EQUAL( iv[ 2 ], 23 );
		iv.resize( 18 );
		BOOST_CHECK_EQUAL( iv.size(), 18ul );
		BOOST_CHECK_EQUAL( iv.capacity(), 19ul );
		BOOST_CHECK_EQUAL( iv[ 2 ], 23 );
		BOOST_CHECK_EQUAL( iv[ 6 ], 0 );
		BOOST_CHECK_EQUAL( iv[ 17 ], 0 );
		BOOST_CHECK_THROW( iv[ 18 ], std::out_of_range );
	}
	{
		vector< int > iv;
		for ( int i = 0 ; i < 150 ; ++i )
			iv.push_back( i );
		BOOST_CHECK_EQUAL( std::accumulate( iv.begin(), iv.end() , 0 ), 150 * ( static_cast< double >( 149 + 0 ) / 2 ) );
		for ( vector< int >::iterator i = iv.begin() ; i != iv.end() ; ++i )
			*i = 10;
		BOOST_CHECK_EQUAL( std::accumulate( iv.begin(), iv.end() , 0 ), 10 * 150 );
	}
	{
		vector< int > iv;
		for ( int i = 0 ; i < 150 ; ++i )
			iv.push_back( i );
		iv.insert( 0, 20 );
		BOOST_CHECK_EQUAL( iv.size(), 151ul );
		BOOST_CHECK_EQUAL( iv.capacity(), 256ul );
		BOOST_CHECK_EQUAL( iv[ 0 ], 20 );
		BOOST_CHECK_EQUAL( iv[ 1 ], 0 );
		BOOST_CHECK_EQUAL( iv[ 150 ], 149 );
	}
}

