#ifndef _TASK5_4_TEMPLATE_FUNCTIONS_H_
#define _TASK5_4_TEMPLATE_FUNCTIONS_H_

#include <functional>
#include <vector>
#include <map>
#include <list>
#include <set>

namespace task5_4
{
	template< bool delete_first, typename Container >
	void clear_container( Container& c )
	{
		c.clear();
	}

	template<bool delete_first, typename T>
	void clear_container( std::vector<T*>& c )
	{
		if( delete_first )
		{
			for( auto it = c.begin(); it != c.end(); it++ )
			{
				T *p = *it;
				delete p;
			}
		}

		c.clear();
	}

	template<bool delete_first, typename T>
	void clear_container( std::list<T*>& c )
	{
		if( delete_first )
		{
			for( auto it = c.begin(); it != c.end(); it++ )
			{
				T *p = *it;
				delete p;
			}
		}

		c.clear();
	}

	template<bool delete_first, typename T>
	void clear_container( std::set<T*>& c )
	{
		if( delete_first )
		{
			for( auto it = c.begin(); it != c.end(); it++ )
			{
				T *p = *it;
				delete p;
			}
		}

		c.clear();
	}

	template< bool delete_first, bool delete_second, typename Container >
	void clear_container( Container& c )
	{
		c.clear();
	}

	template< bool delete_first, bool delete_second, typename K, typename T >
	void clear_container( std::map<K*, T>& m )
	{
		for( auto it = m.begin(); it != m.end(); it++ )
		{
			if( delete_first )
			{
				delete it->first;
			}
		}

		m.clear();
	}

	template< bool delete_first, bool delete_second, typename K, typename T >
	void clear_container( std::map<K, T*>& m )
	{
		for( auto it = m.begin(); it != m.end(); it++ )
		{
			if( delete_second )
			{
				delete it->second;
			}
		}

		m.clear();
	}

	template< bool delete_first, bool delete_second, typename K, typename T >
	void clear_container( std::map<K*, T*>& m )
	{
		for( auto it = m.begin(); it != m.end(); it++ )
		{
			if( delete_first )
			{
				delete it->first;
			}

			if( delete_second )
			{
				delete it->second;
			}
		}

		m.clear();
	}
}


#endif // _TASK5_4_TEMPLATE_FUNCTIONS_H_

