#ifndef _TASK5_4_TEMPLATE_FUNCTIONS_H_
#define _TASK5_4_TEMPLATE_FUNCTIONS_H_

#include <functional>
#include <boost/foreach.hpp>
namespace task5_4
{
	template < bool delete_first, typename Container >
	struct one_arg_cleaner
	{
		void clean( Container& obj)
		{}
	};

	template < typename Container >
	struct one_arg_cleaner < true, Container >
	{
		void clean( Container& obj)
		{
			BOOST_FOREACH( const Container::value_type& item, obj)
				delete item;
		}
	};

	template< bool delete_first, bool delete_second, typename Container >
	struct two_arg_cleaner
	{
		void clean( Container& obj)
		{}
	};

	template< bool delete_first, typename Container >
	struct two_arg_cleaner < delete_first, true, Container >
	{
		void clean( Container& obj)
		{
			BOOST_FOREACH( const Container::value_type& item, obj)
				delete item.second;
		}
	};

	template< bool delete_second, typename Container >
	struct two_arg_cleaner < true, delete_second, Container >
	{
		void clean( Container& obj)
		{
			BOOST_FOREACH( const Container::value_type& item, obj)
				delete item.first;
		}
	};

	template< typename Container >
	struct two_arg_cleaner < true, true, Container >
	{
		void clean( Container& obj)
		{
			BOOST_FOREACH( const Container::value_type& item, obj)
			{
				delete item.first;
				delete item.second;
			}
		}
	};

	template< bool delete_first, typename Container >
	void clear_container( Container& tmp)
	{
		one_arg_cleaner<delete_first,Container> cleaner;
		cleaner.clean(tmp);
		tmp.clear();
	}

	template< bool delete_first, bool delete_second, typename Container >
	void clear_container( Container& tmp)
	{
		two_arg_cleaner<delete_first,delete_second,Container> cleaner;
		cleaner.clean(tmp);
		tmp.clear();
	}
}


#endif // _TASK5_4_TEMPLATE_FUNCTIONS_H_

