#ifndef _TASK5_4_TEMPLATE_FUNCTIONS_H_
#define _TASK5_4_TEMPLATE_FUNCTIONS_H_

#include <functional>
#include <memory>

namespace task5_4
{
//////////////////////////////////////////cDeleteFirst///////////////////////////////////////////////////////////////
    template< bool delete_firs, typename Container>
    class cDeleteFirst
    {
    public:
        cDeleteFirst( Container& )
        {}
    };

    template<typename Container>
    class cDeleteFirst <true, Container>
    {
    public:
        cDeleteFirst( Container& _containe)
        {
            for (auto pointer : _containe)
            {
                delete pointer;
            }
        }
    };

    template< bool delete_first, typename Container >
    void clear_container( Container& _container)
    {
        cDeleteFirst<delete_first, Container> delete_first( _container );
       _container.clear();
    }

//////////////////////////////////////////cDeleteFirstAndSecond///////////////////////////////////////////////////////////////

    template< bool delete_first, bool delete_second, typename Container >
    class cDeleteFirstAndSecond
    {
    public:
        cDeleteFirstAndSecond(Container&)
        {}
    };

    template<typename Container>
    class cDeleteFirstAndSecond< true, true, Container>
    {
    public:
        cDeleteFirstAndSecond(Container& _container)
        {
            for (auto pair_obj : _container)
            {
                delete pair_obj.first;
                delete pair_obj.second;
            }
        }
    };

    template<typename Container>
    class cDeleteFirstAndSecond< false, true, Container>
    {
    public:
        cDeleteFirstAndSecond(Container& _container)
        {
            for (auto pair_obj : _container)
            {
                delete pair_obj.second;
            }
        }
    };

    template<typename Container>
    class cDeleteFirstAndSecond< true, false, Container>
    {
    public:
        cDeleteFirstAndSecond(Container& _container)
        {
            for (auto pair_obj : _container)
            {
                delete pair_obj.first;
            }
        }
    };

    template< bool delete_first, bool delete_second, typename Container >
    void clear_container( Container& _container)
    {
        cDeleteFirstAndSecond<delete_first, delete_second, Container> delete_first_and_second(_container);
        _container.clear();
    }
}


#endif // _TASK5_4_TEMPLATE_FUNCTIONS_H_

