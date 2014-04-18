#include <iostream>

#include <ts_logger.h>
#include <limited_file_logger.h>

int main()
{
	{
		using namespace system_utilities::common;

		//ts_logger< limited_file_logger< true, true, true, 128 > > logger_(BINARY_DIR "/log_example.txt");
		file_logger<> logger_(BINARY_DIR "/log_example.txt");
		
		logger_.note() << "Hello note";
		logger_.warn() << "Test warning";
		logger_.error( "Serious error" );
	}

}