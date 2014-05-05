#ifndef _TASK5_4_TEMPLATE_FUNCTIONS_H_
#define _TASK5_4_TEMPLATE_FUNCTIONS_H_

#include <functional>


namespace task5_4
{
	template< bool delete_first, typename Container >
	void clear_container( Container& a)
	{
		if (delete_first)
		{
			for (typename Container::const_iterator it = a.begin(); it!= a.end(); ++it)
				delete reinterpret_cast<typename Container::value_type *>(*it);
		}
		a.clear();
	}

	template< bool delete_first, bool delete_second, typename Container >
	struct fs_cleaner
	{
		void clean( Container& a )
		{}
	};

	template< bool delete_first, typename Container >
	struct fs_cleaner < delete_first, true, Container >
	{
		void clean( Container& a )
		{
			for (typename Container:: const_iterator it = a.begin(); it!= a.end(); ++it)
				{
					delete (it->second);
				}
		}
	};

	template< bool delete_second, typename Container >
	struct fs_cleaner < true, delete_second, Container >
	{
		void clean( Container& a )
		{
			for (typename Container:: const_iterator it = a.begin(); it!= a.end(); ++it)
				{
					delete (it->first);
				}
		}
	};

	template< typename Container >
	struct fs_cleaner < true, true, Container >
	{
		void clean( Container& a )
		{
			for (typename Container:: const_iterator it = a.begin(); it!= a.end(); ++it)
				{
					delete (it->first);
					delete (it->second);
				}
		}
	};


	template< bool delete_first, bool delete_second, typename Container >
	void clear_container( Container& a )
	{
		fs_cleaner< delete_first, delete_second, Container > cleaner;

		cleaner.clean( a );

		a.clear();
	}
}


#endif // _TASK5_4_TEMPLATE_FUNCTIONS_H_

