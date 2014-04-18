#ifndef _BAD_ALLOC_BAD_STRING_H_
#define _BAD_ALLOC_BAD_STRING_H_

namespace memory_leak_examples
{
	class bad_string
	{
		char *ptr_;
	public:
		explicit bad_string();
		~bad_string();
	};

}

#endif // _BAD_ALLOC_BAD_STRING_H_
