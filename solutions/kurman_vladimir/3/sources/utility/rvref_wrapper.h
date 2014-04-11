#ifndef _RVREF_WRAPPER_H_
#define _RVREF_WRAPPER_H_

#include <utility>
#include <type_traits>

template <typename T>
struct rvref_wrapper
{
	rvref_wrapper(T && value) : value_(std::move(value))
	{

	}

	rvref_wrapper(rvref_wrapper const & other) : value_(other.get())
	{

	}

	T && get() const
	{
		return std::move(value_);
	}
	mutable T value_;
};

template <typename T>
rvref_wrapper<typename std::decay<T>::type> rvref(T && x)
{
	return std::move(x);
}

#endif // _RVREF_WRAPPER_H_
