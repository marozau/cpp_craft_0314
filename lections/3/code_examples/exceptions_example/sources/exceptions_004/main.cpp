#include <string>
#include <iostream>
#include <exception>

int main()
{
	try
	{
		throw 'c';
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

