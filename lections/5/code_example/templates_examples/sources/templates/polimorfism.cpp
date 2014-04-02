#include "polimorfism.h"


namespace templates
{
	const type::value first_nested::get_type() const
	{
		return type::first_type;
	}
	const type::value second_nested::get_type() const
	{
		return type::second_type;
	}
	const type::value third_nested::get_type() const
	{
		return type::third_type;
	}
	//
	template<>
	const type::value compilation_time_polimorf< type::first_type >::get_type() const
	{
		return type::first_type;
	}
	template<>
	const type::value compilation_time_polimorf< type::second_type >::get_type() const
	{
		return type::second_type;
	}
	template<>
	const type::value compilation_time_polimorf< type::third_type >::get_type() const
	{
		return type::third_type;
	}
}
