#ifndef _TASK5_4_TEMPLATE_FUNCTIONS_H_
#define _TASK5_4_TEMPLATE_FUNCTIONS_H_

#include <functional>
#include <stdio.h>

namespace task5_4
{
	template< bool delete_first, typename Container >

    void clear_container( Container&  cont)
    {
        for(auto ptr : cont)
            if(delete_first)
                delete reinterpret_cast< typename Container::value_type * >( ptr );
        cont.clear();
    }

    template< bool delete_first, bool delete_second, typename Container >
    typename std::enable_if<!std::is_pointer< typename Container::mapped_type >::value>::type
    clear_container( Container& cont)
    {
        for(auto ptr : cont){
            if(delete_first)
                delete reinterpret_cast< typename Container::key_type *> ( ptr.first );
        }
        cont.clear();
    }

    template< bool delete_first, bool delete_second, typename Container >
    typename std::enable_if<std::is_pointer< typename Container::mapped_type >::value >::type
    clear_container( Container& cont)
    {
        for(auto ptr : cont){
            if(delete_first)
                delete reinterpret_cast< typename Container::key_type * >( ptr.first );
                delete  ptr.second;
        }
        cont.clear();
    }

}
#endif // _TASK5_4_TEMPLATE_FUNCTIONS_H_

