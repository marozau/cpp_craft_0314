#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW

#include <bad_string.h>

int main()
{
	//_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE ); // enable file output
	//_CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT ); // set file to stdout

	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );

	{
		memory_leak_examples::bad_string bs1;
		memory_leak_examples::bad_string bs2;
	}

//	_CrtMemState s1, s2, s3;
//	_CrtMemCheckpoint( &s1 );

	{
		memory_leak_examples::bad_string bs3;
	}

//	_CrtMemCheckpoint( &s2 );

//	if ( _CrtMemDifference( &s3, &s1, &s2) )
//		_CrtMemDumpStatistics( &s3 );

	{
		memory_leak_examples::bad_string bs4;
		memory_leak_examples::bad_string bs5;
	}

	{
		int* p_c = (int*) malloc( 10 * sizeof(int) );
		int* p_cpp = new int(3);
		int* p_cpp_array = new int[25];
	}
//	_CrtMemDumpAllObjectsSince( &s2 );
//	_CrtDumpMemoryLeaks();

}
