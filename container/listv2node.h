#ifndef LISTV2NODE_H
#define LISTV2NODE_H

#include <memory>
#include <iostream>

template <typename T> class ListV2_iterator;


template <typename T>
class ListV2Node{
public:
    friend class ListV2_iterator<T>;

    template<typename ... Args>
    ListV2Node(Args && ... args):elem(std::forward<Args>(args)...),next(nullptr){
    }


    ~ListV2Node() {        
    }

    T elem;
    ListV2Node<T> *next;
};

#endif // LISTV2NODE_H
