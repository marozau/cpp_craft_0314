#include "test_registrator.h"

#include <bad_string.h>

void memory_leak_examples::tests_::bad_string_tests()
{
	//_CrtMemState s1, s2, s3;
	//_CrtMemCheckpoint( &s1 );

	bad_string bd;

	//_CrtMemCheckpoint( &s2 );
	//if ( _CrtMemDifference( &s3, &s1, &s2) )
	//{
	//	_CrtMemDumpStatistics( &s3 );
	//	BOOST_ERROR( "Memory leak detected" );
	//}
}
