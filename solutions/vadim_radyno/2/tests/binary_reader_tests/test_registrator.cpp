#include "test_registrator.h"

#include <boost/test/unit_test.hpp>

boost::unit_test_framework::test_suite* init_unit_test_suite( int argc, char* argv[] )
{
	using boost::unit_test_framework::test_case;

    boost::unit_test_framework::test_suite* ts1 = BOOST_TEST_SUITE( "binary_reader tests" );
	boost::unit_test::unit_test_log.set_threshold_level( boost::unit_test::log_messages );

	using namespace binary_reader::tests_;

//	ts1->add( BOOST_TEST_CASE( &test_market_message ) );	


#ifdef RUN_PERFORMANCE_TESTS
#endif

	return ts1;
}
