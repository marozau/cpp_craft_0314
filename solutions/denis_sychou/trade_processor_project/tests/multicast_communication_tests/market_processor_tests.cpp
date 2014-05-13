#include "test_registrator.h"

#include <market_processor.h>
#include <fstream>

void multicast_communication::tests_::market_processor_tests()
{
	processor_ptr proc_ptr( new processor( "/tests/data/market_data.dat" ) );

	std::string temp;

	std::ifstream input( SOURCE_DIR "/tests/data/quote_tests.txt" );
	while( !input.eof() )
	{
		std::getline( input, temp );
		BOOST_CHECK_NO_THROW( proc_ptr->parse( temp, QUOTE ) );
	}
	input.close();

	input.open(  SOURCE_DIR "/tests/data/trade_tests.txt" );
	while( !input.eof() )
	{
		std::getline( input, temp );
		BOOST_CHECK_NO_THROW( proc_ptr->parse( temp, TRADE ) );
	}
	input.close();
}
