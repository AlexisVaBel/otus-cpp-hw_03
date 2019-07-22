#ifndef LISTV2NODE_H
#define LISTV2NODE_H

#include <memory>
#include <iostream>

template <typename T> class ListV2_iterator;


template <typename T>
class ListV2Node{


public:
    friend class ListV2_iterator<T>;

    ListV2Node(const T& t, ListV2Node<T> *next): elem(t), next(next) {

    }

    ListV2Node(const T&& t, ListV2Node<T> *next): elem(t), next(next) {

    }

    ~ListV2Node() {        
    }

    T elem;
    ListV2Node<T> *next;
};

#endif // LISTV2NODE_H
