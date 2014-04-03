#ifndef _TASK5_4_TEMPLATE_FUNCTIONS_H_
#define _TASK5_4_TEMPLATE_FUNCTIONS_H_

#include <functional>

namespace task5_4
{
	template< bool delete_first, typename Container >
	void clear_container( Container& )
	{
	}

	template< bool delete_first, bool delete_second, typename Container >
	void clear_container( Container& )
	{
	}
}


#endif // _TASK5_4_TEMPLATE_FUNCTIONS_H_

