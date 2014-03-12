#include <iostream>
#include <stdint.h>

union my_union
{
       char c[4];
       int32_t  i;
};


int main()
{
	my_union z;
	z.i = 256;
	
	std::cout << static_cast< int >( z.c[0] ) << static_cast< int >( z.c[1] ) << static_cast< int >( z.c[2] ) << static_cast< int >( z.c[3] ) << std::endl;

	return 0;
}