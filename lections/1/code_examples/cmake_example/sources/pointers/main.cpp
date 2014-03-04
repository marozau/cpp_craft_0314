#include <iostream>

void f1() 
{
	std::cout << "Empty function" << std::endl;
}
void f2( int i ) 
{
	std::cout << i << std::endl;
}

struct static_member
{
	static void out()
	{
		std::cout << "call static_member::out()" << std::endl;
	}
};

typedef void (*fp1)();
typedef void (*fp2)( int );
typedef std::string::size_type (std::string::*sp)() const;

int main( void )
{
	fp1 f1_ptr = &f1;
	f1_ptr();

	fp2 f2_ptr = &f2;
	f2_ptr( 1 );

	std::string s( "Hello world" );
	sp size_ptr = &std::string::size;
	std::cout << ( s.*size_ptr )() << std::endl;

	fp1 static_ptr = &static_member::out;
	static_ptr();
		
	return 0;
}
