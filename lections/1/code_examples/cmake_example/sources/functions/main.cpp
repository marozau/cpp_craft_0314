#include <iostream>

void f1() 
{
	std::cout << "Empty function" << std::endl;
}
void f2( int i ) 
{
	i = 2;
	std::cout << i << std::endl;
}
void f3( const int i ) 
{
	// i = 3;
}
void f4( int& i ) 
{
	i = 4;
	std::cout << i << std::endl;
}
void f5( const int& i ) 
{
	//i = 5;
}
void f6( int* i ) 
{
	*i = 6;
	delete i;
	i = new int ( 66 );
	std::cout << *i << std::endl;
}
void f7( const int* i ) 
{
	// *i = 7; error
	delete i;
	i = new int ( 77 );
	std::cout << *i << std::endl;
}
void f8( int * const i ) 
{
	*i = 8;
	/*delete i; error
	i = new int ( 88 ); */
	std::cout << *i << std::endl;
}
void f9( const int* const i ) 
{
	/**i = 9;
	delete i; error
	i = new int ( 99 ); */
	
}

int main( void )
{
	f1();	
	f2( 1 );
	f3( 1 );
	

	// f4( 1 );
	int i = 1;
	f4( i );

	int* i_ptr = new int( 3 );
	f6( i_ptr );
	f7( i_ptr );
	f8( i_ptr );

	delete i_ptr;

	return 0;
}
