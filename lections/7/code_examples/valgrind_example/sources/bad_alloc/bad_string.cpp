#include "bad_string.h"

memory_leak_examples::bad_string::bad_string()
{
	ptr_ = new char[ 14 ];
}

memory_leak_examples::bad_string::~bad_string()
{
//	delete ptr_;
}

