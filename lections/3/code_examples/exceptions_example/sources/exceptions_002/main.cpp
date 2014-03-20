#include <string>
#include <iostream>

namespace day_3
{
	class base_exception
	{
	public:
		virtual void what() const
		{
			std::cout << "base_exception" << std::endl;
		}
	};

	class nested_exception : public base_exception
	{
	public:
		virtual void what() const
		{
			std::cout << "nested_exception" << std::endl;
		}
	};
}

int main()
{
	try
	{
		throw day_3::nested_exception();
	}
	catch ( const day_3::nested_exception& e)
	{
		e.what();
	}
	catch( const day_3::base_exception& e )
	{
		e.what();
	}
	
}

