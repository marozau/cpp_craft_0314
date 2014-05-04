#ifndef _TASK5_4_TEMPLATE_FUNCTIONS_H_
#define _TASK5_4_TEMPLATE_FUNCTIONS_H_

#include <functional>
#include <list>

namespace task5_4
{
	template< bool delete_first, typename Container >
	class Cleaner
	{

	public:
		Cleaner(Container& C);
	};

	template< typename Container>
	class Cleaner< false, Container >
	{

	public:
		Cleaner(Container& C)
		{
			C.clear();
		}
	};

	template< typename Container >
	class Cleaner< true, Container >
	{

	public:
		Cleaner(Container& C)
		{
			for (typename Container::iterator i = C.begin(); i != C.end(); i++)
				delete *i;
			
			C.clear();
		}
	};

	template< bool delete_first, typename Container >
	void clear_container(Container& C)
	{
		Cleaner <delete_first, Container>* cleaner = new Cleaner<delete_first, Container>(C);
		delete cleaner;
	};

	template< bool delete_first, bool delete_second, typename Container >
	class Cleaner2
	{
	public:
		Cleaner2(Container& C);
	};

	template< typename Container >
	class Cleaner2< false, false, typename Container >
	{
	public:
		Cleaner2(Container& C)
		{
			C.clear();
		}
	};

	template< typename Container >
	class Cleaner2< true, false, typename Container >
	{
	public:
		Cleaner2(Container& C)
		{
			for (typename Container::const_iterator c_iter = C.begin(); c_iter != C.end(); c_iter++)
				delete c_iter->first;
			C.clear();
		}
	};

	template< typename Container >
	class Cleaner2< false, true, typename Container >
	{
	public:
		Cleaner2(Container& C)
		{
			for (typename Container::const_iterator c_iter = C.begin(); c_iter != C.end(); c_iter++)
				delete c_iter->second;
			C.clear();
		}
	};

	template< typename Container >
	class Cleaner2< true, true, typename Container >
	{
	public:
		Cleaner2(Container& C)
		{
			for (typename Container::const_iterator c_iter = C.begin(); c_iter != C.end(); c_iter++)
			{
				delete c_iter->first;
				delete c_iter->second;
			}
			C.clear();
		}
	};

	template< bool delete_first, bool delete_second, typename Container >
	void clear_container(Container& C)
	{
		Cleaner2< delete_first, delete_second, Container > *cleaner = new Cleaner2< delete_first, delete_second, Container >(C);
		delete cleaner;
	}
}


#endif // _TASK5_4_TEMPLATE_FUNCTIONS_H_

