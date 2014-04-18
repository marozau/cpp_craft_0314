#include "test_registrator.h"

#include <boost/test/unit_test.hpp>

#ifdef BOOST_TEST_DYN_LINK
	bool init_unit_test_suite()
#else
	boost::unit_test_framework::test_suite* init_unit_test_suite( int, char*[] )
#endif
{
	using boost::unit_test_framework::test_case;
	boost::unit_test_framework::test_suite& master_test_suite = boost::unit_test::framework::master_test_suite();

	using namespace multicast_communication::tests_;

	master_test_suite.add( BOOST_TEST_CASE( &quote_message_tests ) );
	master_test_suite.add( BOOST_TEST_CASE( &trade_message_tests ) );

	master_test_suite.add( BOOST_TEST_CASE( &market_data_processor_tests ) );

#ifdef RUN_PERFORMANCE_TESTS
#endif

#ifdef BOOST_TEST_DYN_LINK
	return true;
#else
	return NULL;
#endif
}

#ifdef BOOST_TEST_DYN_LINK

int main( int argc, char* argv[] )
{
    return ::boost::unit_test::unit_test_main( &init_unit_test_suite, argc, argv );
}

#endif