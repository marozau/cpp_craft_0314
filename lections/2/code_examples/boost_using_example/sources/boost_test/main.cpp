
#include <string>
#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/array.hpp>

typedef boost::shared_ptr< std::string > string;
typedef boost::scoped_ptr< std::string > string_ptr;
typedef boost::array< int, 100 > int_array;

string f()
{
	return string( new std::string( "hello shared world" ) );
}

void f2( string_ptr& ptr )
{
	return ptr.reset( new std::string( "wow wow" ) );
}

int_array f3()
{
	int_array a;
	a[ 5 ] = 15;
	return a;
}


int main()
{
	{
		string s = f();
		string s2 = s;
		std::cout << s2->c_str() << std::endl;
	}
	{
		string_ptr ps;
		f2( ps );
		std::cout << ps->c_str() << std::endl;

		// string_ptr sp2 = ps; // uncomment to get in troubles
	}
	{
		int_array ia = f3();
		std::cout << ia[5] << std::endl;
	}
}

