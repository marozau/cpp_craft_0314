#ifndef _TASK5_4_TEMPLATE_FUNCTIONS_H_
#define _TASK5_4_TEMPLATE_FUNCTIONS_H_

#include <functional>
#include <list>

namespace task5_4
{
	template< bool delete_first, typename Container >
	struct first_cleaning
	{
		first_cleaning( Container& C );
	};

	template< typename Container >
	struct first_cleaning< false, Container > 
	{
		first_cleaning( Container& C )
		{
			C.clear();
		}
	};

	template< typename Container >
	struct first_cleaning< true, Container >
	{
		first_cleaning( Container& C )
		{
			for( typename Container::const_iterator c_iter = C.begin(); c_iter != C.end(); c_iter++ )
				delete *c_iter;
			C.clear();
		}
	};

	template< bool delete_first, typename Container >
	void clear_container( Container& C )
	{
		first_cleaning<delete_first, Container> *c_deleting = new first_cleaning<delete_first, Container>( C );
		delete c_deleting;
	}

	template< bool delete_first, bool delete_second, typename Container >
	struct second_cleaning
	{
		second_cleaning( Container& C );
	};

	template< typename Container >
	struct second_cleaning< false, false, typename Container >
	{
		second_cleaning( Container& C )
		{
			C.clear();
		}
	};

	template< typename Container >
	struct second_cleaning< true, false, typename Container >
	{
		second_cleaning( Container& C )
		{
			for( typename Container::const_iterator c_iter = C.begin(); c_iter != C.end(); c_iter++ )
				delete c_iter->first;
			C.clear();
		}
	};

	template< typename Container >
	struct second_cleaning< false, true, typename Container >
	{
		second_cleaning( Container& C )
		{
			for( typename Container::const_iterator c_iter = C.begin(); c_iter != C.end(); c_iter++ )
				delete c_iter->second;
			C.clear();
		}
	};

	template< typename Container >
	struct second_cleaning< true, true, typename Container >
	{
		second_cleaning( Container& C )
		{
			for( typename Container::const_iterator c_iter = C.begin(); c_iter != C.end(); c_iter++ )
			{
				delete c_iter->first;
				delete c_iter->second;
			}
			C.clear();
		}
	};

	template< bool delete_first, bool delete_second, typename Container >
	void clear_container( Container& C )
	{
		second_cleaning< delete_first, delete_second, Container > *c_deleting = new second_cleaning< delete_first, delete_second, Container >( C );
		delete c_deleting;
	}
}


#endif // _TASK5_4_TEMPLATE_FUNCTIONS_H_

