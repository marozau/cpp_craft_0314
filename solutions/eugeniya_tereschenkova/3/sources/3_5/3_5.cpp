#include "small_buffer.h"

int main()
{
	static const int file_count = 999;

  	try
  	{
    	task3_5::solution s( file_count );
    	s.start();
  	}
	catch(...) 
	{
    	return 1;
  	}

	return 0;
}
