#include "test_registrator.h"

#include <separator.h>
#include <main_processor.h>

#include <fstream>
#include <boost\lexical_cast.hpp>

void multicast_communication::tests_::separator_processor_tests(){
	using namespace std;
	ifstream inn;
	string message;
	const main_processor_ptr proc = main_processor_ptr (new main_processor ("market_data.dat"));
	for (size_t i = 0; i<8; ++i){
		inn.open(boost::lexical_cast<string>(SOURCE_DIR)+"/tests/data/233.200.79."+boost::lexical_cast<string>(i)+".udp", ios_base::in);
		getline(inn,message);
		BOOST_CHECK_NO_THROW (separator_ptr spt = separator_ptr (new separator (message,QUOTE,proc));)
		inn.close();
	}
	for (size_t i = 128; i<140; ++i){
		inn.open(boost::lexical_cast<string>(SOURCE_DIR)+"/tests/data/233.200.79."+boost::lexical_cast<string>(i)+".udp", ios_base::in);
		getline(inn,message);
		BOOST_CHECK_NO_THROW (separator_ptr spt = separator_ptr (new separator (message,TRADE,proc));)
		inn.close();
	}
	
}
