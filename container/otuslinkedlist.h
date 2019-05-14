#ifndef OTUSLINKEDLIST_H
#define OTUSLINKEDLIST_H

#include <iostream>
#include <bits/allocator.h>


template <class U>
struct OtusListNode
{
    OtusListNode(U someU):m_holdingVal(someU){

    }

    ~OtusListNode(){
        delete m_previos;
        delete m_next;
    }

    OtusListNode<U> *m_next;
    OtusListNode<U> *m_previos;
    U   m_holdingVal;
};

template <class T,
          class Allocator = std::allocator<OtusListNode<T>>
          >
class  OtusLinkeList {
    using allocator_type    = Allocator;
    using value_type        = typename allocator_type::value_type;
    using reference         = typename allocator_type::reference;
    using pointer           = typename allocator_type::pointer;
    using const_reference   = typename allocator_type::const_reference;
    using size_type         = typename allocator_type::size_type;
    using iterator          = typename allocator_type::pointer;

public:
    // constructor destructor section
    OtusLinkeList(allocator_type alloc ={}): m_alloc(alloc)
    {
        m_pnt = m_alloc.allocate(1);
        std::cout << __PRETTY_FUNCTION__ <<" 1 allocate " <<  std::endl;
    }

    void append(T someT){
        m_alloc.construct(m_pnt,someT);
        auto p = m_alloc.allocate(1);
        m_pnt->m_next = p;
        m_pnt = p;
    }


    T last(){
        auto t = m_pnt->m_holdingVal;
        return t;
    }


    OtusLinkeList(const OtusLinkeList&){
        std::cout << __PRETTY_FUNCTION__ <<" 2 allocate "<< std::endl;
    }

    OtusLinkeList(const OtusLinkeList&& a)noexcept{
        std::cout << __PRETTY_FUNCTION__ <<" 3 allocate "<< std::endl;
    }

    ~OtusLinkeList(){
        m_alloc.~Allocator();
//        delete m_pnt;
    }

private:
    allocator_type  m_alloc;

    OtusListNode<T> *m_pnt;

};
#endif // OTUSLINKEDLIST_H
