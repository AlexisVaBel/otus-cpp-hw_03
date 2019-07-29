#ifndef LISTV2NODE_H
#define LISTV2NODE_H

#include <memory>
#include <iostream>

template <typename T> class ListV2_iterator;


template <typename T>
class ListV2Node{
public:
    friend class ListV2_iterator<T>;


    ListV2Node(T&& u):elem(std::move(u)),next(nullptr){
    }

    ListV2Node(T& u):elem(u),next(nullptr){
    }


    ~ListV2Node() {        
    }

    T elem;
    ListV2Node<T> *next;
};

#endif // LISTV2NODE_H
