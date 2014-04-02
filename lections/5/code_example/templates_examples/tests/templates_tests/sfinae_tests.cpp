#include "test_registrator.h"

#include "sfinae_inheritance.h"
#include "simple_sfinae.h"

void templates::tests_::sfinae_tests()
{
	 f<with_foo>(10);
	 f<int>(10);

	BOOST_CHECK_EQUAL( inheritance_test< A1 >::check, true );
	BOOST_CHECK_EQUAL( inheritance_test< B1 >::check, false );
}
