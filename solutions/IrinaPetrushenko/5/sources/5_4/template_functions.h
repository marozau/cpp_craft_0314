#ifndef _TASK5_4_TEMPLATE_FUNCTIONS_H_
#define _TASK5_4_TEMPLATE_FUNCTIONS_H_

#include <functional>
#include <algorithm> 
#include <stdio.h>
#include <fstream>
#include <iostream>

namespace task5_4
{
	
	template< bool delete_first, typename Container >
	void clear_container( Container& v)
	{
		if (delete_first) {
			for( typename Container::const_iterator it = v.begin(); it != v.end(); ++it )
				delete reinterpret_cast<typename Container::value_type *>(*it);
		}
		v.clear();
	}
	
	

	template< bool delete_first, bool delete_second, typename Container >
	void clear_container( Container& v)
	{
			for_clear_container <delete_first,delete_second, typename Container> f = for_clear_container <delete_first,delete_second,typename Container> (v);		
	}

	template< bool delete_first, bool delete_second, typename Container >
	struct for_clear_container{
		for_clear_container (Container& v){
			if (delete_first) {
				for( typename Container::iterator it = v.begin(); it != v.end(); ++it )
						delete (*it).first;
					
			}
			if (delete_second) {
				for( typename Container::iterator it = v.begin(); it != v.end(); ++it )
						delete (*it).second;
					
			}
			v.clear();
		}
	};
	template< typename Container >
	struct for_clear_container<true, true,typename Container>{
			for_clear_container(Container& v){
					for( typename Container::iterator it = v.begin(); it != v.end(); ++it ){
						delete (*it).first;
						delete (*it).second;
					}
					v.clear();
			}
	};
	template< typename Container >
	struct for_clear_container<true, false,typename Container>{
			for_clear_container(Container& v){
					for( typename Container::iterator it = v.begin(); it != v.end(); ++it )
						delete (*it).first;
					
					v.clear();
			}
	};
	template< typename Container >
	struct for_clear_container<false, true,typename Container>{
			for_clear_container(Container& v){
					for( typename Container::iterator it = v.begin(); it != v.end(); ++it )
						delete (*it).second;
					v.clear();
			}
	};
	template< typename Container >
	struct for_clear_container<false, false,typename Container>{
			for_clear_container(Container& v){
					v.clear();
			}
	};
	
}


#endif // _TASK5_4_TEMPLATE_FUNCTIONS_H_

