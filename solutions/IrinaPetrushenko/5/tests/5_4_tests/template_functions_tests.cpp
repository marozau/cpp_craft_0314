#include "test_registrator.h"

#include <template_functions.h>

#include <vector>
#include <map>
#include <list>
#include <set>
#include <stdexcept>

void task5_4::tests_::template_functions_vector_tests()
{
	{
		std::vector< int > v1( 15, 0 );

		BOOST_CHECK_NO_THROW( clear_container< false >( v1 ) );
		BOOST_CHECK_EQUAL( v1.empty(), true );

		int v1_content[] = { 15, 18, 43, 76 };
		std::copy( v1_content, v1_content + 4, std::back_inserter( v1 ) );

		BOOST_CHECK_NO_THROW( clear_container< false >( v1 ) );
		BOOST_CHECK_EQUAL( v1.empty(), true );
	}
	{
		std::vector< int* > v2;
		v2.push_back( new int( 4 ) );
		v2.push_back( new int( 8 ) );
		v2.push_back( new int( 2 ) );
		v2.push_back( new int( 5 ) );
		v2.push_back( new int( 9 ) );

		BOOST_CHECK_NO_THROW( clear_container< true >( v2 ) );
		BOOST_CHECK_EQUAL( v2.empty(), true );
	}
}
void task5_4::tests_::template_functions_map_tests()
{
	{
		std::map< int, std::string > m1;
		m1[ 14 ] = "just a string";
		m1[ 140 ] = "just another string";
		m1[ 314 ] = "just a test string";

		BOOST_CHECK_NO_THROW( ( clear_container< false, false >( m1 ) ) );
		BOOST_CHECK_EQUAL( m1.empty(), true );
	}
	{
		std::map< int*, std::string > m2;
		m2[ new int( 45 ) ] = "just a string";
		m2[ new int( 140 ) ] = "just a test string";
		m2[ new int( 314 ) ] = "just another string";

		BOOST_CHECK_NO_THROW( ( clear_container< true, false >( m2 ) ) );
		BOOST_CHECK_EQUAL( m2.empty(), true );
	}
	{
		std::map< int, std::string* > m3;
		m3[ 82 ] = new std::string( "heap string" );
		m3[ 140 ] = new std::string( "another heap string" );
		m3[ 314 ] = new std::string( "say hello to 5_4 task" );

		BOOST_CHECK_NO_THROW( ( clear_container< false, true >( m3 ) ) );
		BOOST_CHECK_EQUAL( m3.empty(), true );
	}
	{
		std::map< double*, std::string* > m3;
		m3[ new double(82.23) ] = new std::string( "heap string" );
		m3[ new double(140.65) ] = new std::string( "another heap string" );
		m3[ new double(314.34) ] = new std::string( "say hello to 5_4 task" );

		BOOST_CHECK_NO_THROW( ( clear_container< true, true >( m3 ) ) );
		BOOST_CHECK_EQUAL( m3.empty(), true );
	}
}
void task5_4::tests_::template_functions_list_tests()
{
	{
		std::list< char > l1;
		l1.push_back( 'a' );
		l1.push_back( 'c' );
		l1.push_back( 'b' );
		l1.push_back( 'd' );

		BOOST_CHECK_NO_THROW( ( clear_container< false >( l1 ) ) );
		BOOST_CHECK_EQUAL( l1.empty(), true );
	}
	{
		std::list< char* > l2;
		l2.push_back( new char('a') );
		l2.push_back( new char('c') );
		l2.push_back( new char('b') );
		l2.push_back( new char('d') );

		BOOST_CHECK_NO_THROW( ( clear_container< true >( l2 ) ) );
		BOOST_CHECK_EQUAL( l2.empty(), true );
	}
}
void task5_4::tests_::template_functions_set_tests()
{
	{
		std::set< char > s1;
		s1.insert( 'a' );
		s1.insert( 'c' );
		s1.insert( 'b' );
		s1.insert( 'd' );

		BOOST_CHECK_NO_THROW( ( clear_container< false >( s1 ) ) );
		BOOST_CHECK_EQUAL( s1.empty(), true );
	}
	{
		std::set< char* > s2;
		s2.insert( new char('a') );
		s2.insert( new char('c') );
		s2.insert( new char('b') );
		s2.insert( new char('d') );

		BOOST_CHECK_NO_THROW( ( clear_container< true >( s2 ) ) );
		BOOST_CHECK_EQUAL( s2.empty(), true );
	}
}
