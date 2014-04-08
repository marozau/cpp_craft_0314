#ifndef _TASK5_4_TEMPLATE_FUNCTIONS_H_
#define _TASK5_4_TEMPLATE_FUNCTIONS_H_

#include <functional>

namespace task5_4
{
	template<bool delete_first, typename Container>
	typename std::enable_if<std::is_pointer<typename Container::value_type>::value>::type clear_container(Container & cont)
	{
		if (delete_first)
			for (Container::value_type ptr : cont)
				delete ptr;
		cont.clear();
	}

	template<bool delete_first, typename Container>
	typename std::enable_if<!std::is_pointer<typename Container::value_type>::value>::type clear_container(Container & cont)
	{
		cont.clear();
	}

	template<bool delete_first, bool delete_second, typename Container>
	typename std::enable_if<!std::is_pointer<typename Container::key_type>::value &&
		!std::is_pointer<typename Container::mapped_type>::value>::type clear_container(Container & cont)
	{
		cont.clear();
	}

	template<bool delete_first, bool delete_second, typename Container>
	typename std::enable_if<std::is_pointer<typename Container::key_type>::value &&
		!std::is_pointer<typename Container::mapped_type>::value>::type clear_container(Container & cont)
	{
		if (delete_first)
			for (auto ptrAndVal : cont)
				delete ptrAndVal.first;
		cont.clear();
	}

	template<bool delete_first, bool delete_second, typename Container>
	typename std::enable_if<!std::is_pointer<typename Container::key_type>::value &&
		std::is_pointer<typename Container::mapped_type>::value>::type clear_container(Container & cont)
	{
		if (delete_second)
			for (auto keyAndPtr : cont)
				delete keyAndPtr.second;
		cont.clear();
	}

	template<bool delete_first, bool delete_second, typename Container>
	typename std::enable_if<std::is_pointer<typename Container::key_type>::value &&
		std::is_pointer<typename Container::mapped_type>::value, void>::type clear_container(Container & cont)
	{
		if (delete_first)
			for (auto ptrAndPtr : cont)
				delete ptrAndPtr.first;
		if (delete_second)
			for (auto ptrAndPtr : cont)
				delete ptrAndPtr.second;
		cont.clear();
	}
}

#endif // _TASK5_4_TEMPLATE_FUNCTIONS_H_
