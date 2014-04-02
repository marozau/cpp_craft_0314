#ifndef _TEMPLATES_POLIMORFISM_H_
#define _TEMPLATES_POLIMORFISM_H_

namespace templates
{
	namespace type
	{
		enum value
		{
			first_type,
			second_type,
			third_type
		};
	}
	class run_time_polimorf_prototype
	{
	public:
		virtual const type::value get_type() const = 0;
	};
	class first_nested : public run_time_polimorf_prototype
	{
	public:
		virtual const type::value get_type() const;
	};
	class second_nested : public run_time_polimorf_prototype
	{
	public:
		virtual const type::value get_type() const;
	};
	class third_nested : public run_time_polimorf_prototype
	{
	public:
		virtual const type::value get_type() const;
	};
	//

	template< type::value T >
	class compilation_time_polimorf
	{
	public:
		const type::value get_type() const;
	};
	template<>
	const type::value compilation_time_polimorf< type::first_type >::get_type() const;
	template<>
	const type::value compilation_time_polimorf< type::second_type >::get_type() const;
	template<>
	const type::value compilation_time_polimorf< type::third_type >::get_type() const;
}

#endif // _TEMPLATES_POLIMORFISM_H_
