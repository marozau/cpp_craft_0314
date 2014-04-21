#include <bad_string.h>

int main()
{

	{
		memory_leak_examples::bad_string bs1;
		memory_leak_examples::bad_string bs2;
	}
	
	{
		memory_leak_examples::bad_string bs3;
	}

	{
		memory_leak_examples::bad_string bs4;
		memory_leak_examples::bad_string bs5;
	}

}
