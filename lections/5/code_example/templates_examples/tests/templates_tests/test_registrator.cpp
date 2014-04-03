#include "test_registrator.h"

#include <boost/test/unit_test.hpp>

boost::unit_test_framework::test_suite* init_unit_test_suite( int argc, char* argv[] )
{
	using boost::unit_test_framework::test_case;

    boost::unit_test_framework::test_suite* ts1 = BOOST_TEST_SUITE( "templates tests" );
	boost::unit_test::unit_test_log.set_threshold_level( boost::unit_test::log_messages );

	using namespace templates::tests_;

	ts1->add( BOOST_TEST_CASE( &function_1_tests ) );	
	ts1->add( BOOST_TEST_CASE( &function_2_tests ) );	
	ts1->add( BOOST_TEST_CASE( &function_3_tests ) );
	ts1->add( BOOST_TEST_CASE( &function_4_tests ) );
	ts1->add( BOOST_TEST_CASE( &function_5_tests ) );

	ts1->add( BOOST_TEST_CASE( &vector_tests ) );
	ts1->add( BOOST_TEST_CASE( &stack_tests ) );

	ts1->add( BOOST_TEST_CASE( &calc_in_compile_time) );

	ts1->add( BOOST_TEST_CASE( &sfinae_tests ) );

	ts1->add( BOOST_TEST_CASE( &polimorfism_tests ) );	

#ifdef RUN_PERFORMANCE_TESTS
#endif

	return ts1;
}
