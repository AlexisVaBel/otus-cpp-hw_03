#ifndef LISTV2NODE_H
#define LISTV2NODE_H

#include <memory>
#include <iostream>

template <typename T> class ListV2_iterator;


template <typename T>
class ListV2Node{
public:
    friend class ListV2_iterator<T>;

    template <typename U>
    ListV2Node(U&& u, ListV2Node<T> *nxt):elem(std::forward<U>(u)),next(nxt){
//        std::cout << __PRETTY_FUNCTION__ << " lvalue overload"<<std::endl;
    }

    ~ListV2Node() {        
    }

    T elem;
    ListV2Node<T> *next;
};

#endif // LISTV2NODE_H
