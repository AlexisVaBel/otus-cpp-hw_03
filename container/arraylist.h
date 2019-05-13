#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>
#include <memory>

namespace otus_container{
    static int  ARRLST_DEFAULT_LNG = 10;

    template <class T>
    class ARR_LST_TAIL{

    };

    template <class T,
              class Allocator = std::allocator<T>
              >
    class  ArrayList {
        using allocator_type    = Allocator;
        using value_type        = typename allocator_type::value_type;
        using reference         = typename allocator_type::reference;
        using pointer           = typename allocator_type::pointer;
        using const_reference   = typename allocator_type::const_reference;
        using size_type         = typename allocator_type::size_type;
        using iterator          = typename allocator_type::pointer;


    };
}
// preserving place for 10 elements by default
#endif // ARRAYLIST_H
