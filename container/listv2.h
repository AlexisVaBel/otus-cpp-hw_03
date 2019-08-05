#ifndef LISTV2_H
#define LISTV2_H

#include <listv2node.h>


#include <memory>
//#include <iostream>



template <typename T>
class ListV2_iterator: public std::iterator< std::forward_iterator_tag, T>
{
    friend class ListV2Node<T>;
public:
    ListV2_iterator(ListV2Node<T> *pnt): m_pnt(pnt){}

    T& operator*(){
        return m_pnt->elem;
    }
    const ListV2_iterator<T> & operator++(){
        m_pnt  = m_pnt->next;
        return *this;
    }

    bool operator!=(const ListV2_iterator<T> &other) const{
        return this->m_pnt != other.m_pnt;
    }
private:
    ListV2Node<T> *m_pnt;

};


template <typename T, class Allocator = std::allocator<T> >
class ListV2
{
public:
    using  iterator             = ListV2_iterator<T>;
    using  allocator_type       = Allocator;
    using  pointer              = typename std::allocator_traits<allocator_type>::pointer;
    using  const_pointer        = typename std::allocator_traits<allocator_type>::const_pointer;

    using  rebindeAllocator     = typename std::allocator_traits<allocator_type>::template rebind_alloc<ListV2Node<T>>;
    using  size_type            = typename allocator_type::size_type;

public:
    explicit ListV2(rebindeAllocator alloc = {}):m_curAlloc(rebindeAllocator(alloc)), head(nullptr), tail(nullptr){}

    iterator begin() {return iterator(head);}
    iterator end()   {return iterator(nullptr);}

    iterator cbegin() const {return iterator(head);}
    iterator cend()   const {return iterator(nullptr);}


    bool empty() const {return head == nullptr;}


    // copy constructor
    // allocator should be not the same
    ListV2(const ListV2 &that):m_curAlloc(rebindeAllocator()), head(nullptr), tail(nullptr){
        auto it = that.cbegin();
        while(it != that.cend()){
            this->push_back(*it);
            ++it;
        }
    }


    // move constructor
    ListV2(ListV2 &&that):m_curAlloc(std::move(that.m_curAlloc)),head(nullptr),tail(nullptr){
        std::swap(head,that.head);
        std::swap(tail,that.tail);
    }


    ~ListV2(){
        auto toDelete = head;
        while (toDelete != nullptr) {
            head = head->next;
            m_curAlloc.destroy(toDelete);
            m_curAlloc.deallocate(toDelete,1);
            toDelete = head;
        }
    }


    template <typename... U>
    void push_back(U&&... elem){
        auto newNode = m_curAlloc.allocate(1);
        m_curAlloc.construct(newNode,std::forward<U>(elem)...);
        if(head == nullptr){
            head = newNode;
        }
        else{
            tail->next = newNode;
        }
        tail = newNode;
    }



private:
    rebindeAllocator  m_curAlloc;
    ListV2Node<T>     *head, *tail;
};

#endif // LISTV2_H
