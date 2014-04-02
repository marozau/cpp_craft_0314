#ifndef _TEMPLATES_FACTORIAL_AND_FIBONACCI_H_
#define _TEMPLATES_FACTORIAL_AND_FIBONACCI_H_

namespace templates
{
	template< int v >
	struct factorial
	{
		enum { value = v * factorial< v - 1>::value };
	};
	template<>
	struct factorial<0>
	{
		enum { value = 1 };
	};

	//
	template< long long v >
	struct fibonacci
	{
		static const long long value = fibonacci< v - 1 >::value 
			+ fibonacci< v - 2>::value;
	};

	template<>
	struct fibonacci< 0 >
	{
		static const long long value = 0;
	};
	template<>
	struct fibonacci< 1 >
	{
		static const long long value = 1;
	};

}

#endif // _TEMPLATES_FACTORIAL_AND_FIBONACCI_H_