#include "test_registrator.h"

#include <polimorfism.h>

#include <boost/shared_ptr.hpp>

void templates::tests_::polimorfism_tests()
{
	compilation_time_polimorf< type::second_type > t1;
	BOOST_CHECK_EQUAL( t1.get_type(), type::second_type );


	boost::shared_ptr< run_time_polimorf_prototype > t2;
	t2.reset( new second_nested() );
	BOOST_CHECK_EQUAL( t2->get_type(), type::second_type );	
}