#include "test_registrator.h"

#include "factorial_and_fibonacci.h"

void templates::tests_::calc_in_compile_time()
{
	const int fact = factorial< 6 >::value;
	BOOST_CHECK_EQUAL( fact, 720 );

	const long long fib = fibonacci< 10 >::value;
	BOOST_CHECK_EQUAL( fib, 55 );
}