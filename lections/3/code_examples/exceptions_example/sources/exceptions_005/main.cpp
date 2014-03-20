#include <string>
#include <iostream>
#include <exception>

void f()
{
	try
	{
		throw int(42);
	}
	catch (...)
	{
		std::cout << "... in f()" << std::endl;
		throw;
	}
}

int main()
{
	try
	{
		f();
	}
	catch( int e )
	{
		std::cout << "Int exception: " << e << std::endl;
	}
	catch( ... )
	{
		std::cout << "Unhandled exception" << std::endl;
	}
}

