#include <string>
#include <iostream>

namespace day_3
{
	class my_exception
	{
	};

	class another_exception
	{
	};
}

using namespace day_3;

int main()
{
	try
	{
		throw my_exception();
	}
	catch( my_exception )
	{
		std::cout << "my exception was catched!" << std::endl;
	}
	catch( ... )
	{
		std::cout << "unknown exception was catched!" << std::endl;
	}
	
}

