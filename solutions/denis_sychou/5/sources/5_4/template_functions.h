#ifndef _TASK5_4_TEMPLATE_FUNCTIONS_H_
#define _TASK5_4_TEMPLATE_FUNCTIONS_H_

#include <functional>
#include <boost\foreach.hpp>

namespace task5_4
{
	template< bool delete_first, typename Container >
	struct Cleaner
	{
		void clean( Container &storage )
		{

		}
	};

	template < typename Container >
	struct Cleaner < true, Container >
	{
		void clean( Container &storage )
		{
			BOOST_FOREACH( const Container::value_type& var, storage )
				delete var;
		}
	};

	template< bool delete_first, bool delete_second, typename Container >
	struct Cleaner2nd
	{
		void clean( Container &storage )
		{

		}
	};

	template< bool delete_first, typename Container >
	struct Cleaner2nd < delete_first, true, Container >
	{
		void clean( Container &storage )
		{
			BOOST_FOREACH( const Container::value_type& var, storage )
				delete var.second;
		}
	};

	template< bool delete_second, typename Container >
	struct Cleaner2nd < true, delete_second, Container >	
	{
		void clean( Container &storage )
		{
			BOOST_FOREACH( const Container::value_type& var, storage )
				delete var.first;
		}
	};
	template< typename Container >
	struct Cleaner2nd < true, true, Container >	
	{
		void clean( Container &storage )
		{
			BOOST_FOREACH( const Container::value_type& var, storage )
			{
				delete var.first;
				delete var.second;
			}
		}
	};


	template< bool delete_first, typename Container >
	void clear_container( Container& storage )
	{
		Cleaner< delete_first, Container > cleaner;

		cleaner.clean( storage );

		storage.clear();
	}

	template< bool delete_first, bool delete_second, typename Container >
	void clear_container( Container& storage )
	{
		Cleaner2nd< delete_first, delete_second, Container > cleaner;

		cleaner.clean( storage );

		storage.clear();
	}
}


#endif // _TASK5_4_TEMPLATE_FUNCTIONS_H_

