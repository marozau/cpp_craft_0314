#ifndef _LISTENER_
#define _LISTENER_

#include <boost\function.hpp>

namespace multicast_communication
{
	template < class T>
	class listener
	{
		typedef boost::function<void(T)> RetFunc;
		RetFunc _ret_func;

	public:
		listener(RetFunc);
		void Start();
	};
}
#endif //_LISTENER_