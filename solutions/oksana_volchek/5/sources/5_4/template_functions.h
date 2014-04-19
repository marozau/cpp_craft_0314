#ifndef _TASK5_4_TEMPLATE_FUNCTIONS_H_
#define _TASK5_4_TEMPLATE_FUNCTIONS_H_

#include <functional>
#include <map>

namespace task5_4
{
	
	template< bool delete_first, typename Container >
	void clear_container (Container & cont)
	{
		if (delete_first == true){
			for(typename Container::iterator iter = cont.begin(); iter != cont.end(); ++iter){
				delete [] reinterpret_cast<void*>(*iter);
			}
		}
		cont.clear();
	}

	template< bool delete_first, bool delete_second, typename Container >
	void clear_container(Container & cont)
	{
		cont.clear();
	}

	template< bool delete_first, bool delete_second, typename T, typename U >
	void clear_container(std::map<T, U> & mp)
	{
		if (delete_first == false && delete_second == false){
			mp.clear();
		}
	}

	template< bool delete_first, bool delete_second, typename T, typename U >
	void clear_container(std::map<T*, U> & mp)
	{
		if (delete_first == true && delete_second == false){
			for(std::map<T*, U>::iterator iter = mp.begin(); iter != mp.end(); ++iter){
				delete iter->first;
			}
			mp.clear();
		}
	}

	template< bool delete_first, bool delete_second, typename T, typename U >
	void clear_container(std::map<T, U*> & mp)
	{
		if (delete_first == false && delete_second == true){
			for(std::map<T, U*>::iterator iter = mp.begin(); iter != mp.end(); ++iter){
				delete iter->second;
			}
			mp.clear();
		}
	}

	template< bool delete_first, bool delete_second, typename T, typename U >
	void clear_container(std::map<T*, U*> & mp)
	{
		if (delete_first == true && delete_second == true){
			for(std::map<T*, U*>::iterator iter = mp.begin(); iter != mp.end(); ++iter){
				delete iter->second;
				delete iter->first;
			}
			mp.clear();
		}
	}
}

#endif // _TASK5_4_TEMPLATE_FUNCTIONS_H_

