#ifndef _TEMPLATES_SIMPLE_SFINAE_H_
#define _TEMPLATES_SIMPLE_SFINAE_H_

#include <iostream>

struct with_foo {
	typedef int foo;
};

template <typename T> 
void f(const typename T::foo&)
{
	std::cout << "Hello from f(T::foo)" << std::endl;
}

template <typename T> 
void f(const T&)
{
	std::cout << "Hello from f()" << std::endl;
}

#endif // _TEMPLATES_SIMPLE_SFINAE_H_