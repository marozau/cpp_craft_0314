#include <string>
#include <iostream>
#include <exception>

namespace day_3
{
	class my_exception : public std::exception
	{
	public:
		virtual const char * what() const throw()
		{
			return "my_exception";
		}
		const std::string hello() const
		{
			return "hello exception!";
		}
	};
}

int main()
{
	try
	{
		throw day_3::my_exception();
	}
	catch( const day_3::my_exception& e )
	{
		std::cout << e.hello() << std::endl;
	}
	catch( const std::exception& e )
	{
		std::cout << e.what() << std::endl;
	}
}

