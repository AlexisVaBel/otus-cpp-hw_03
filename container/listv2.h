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
    using iterator = ListV2_iterator<T>;
    using  allocator_type       = Allocator;
    using  pointer              = typename std::allocator_traits<allocator_type>::pointer;
    using  const_pointer        = typename std::allocator_traits<allocator_type>::const_pointer;

    using  rebindeAllocator     = typename std::allocator_traits<allocator_type>::template rebind_alloc<ListV2Node<T>>;
    using  size_type            = typename allocator_type::size_type;

public:
    explicit ListV2(rebindeAllocator alloc = {}):m_curAlloc(rebindeAllocator(alloc)), head(nullptr), tail(nullptr){}


    // copy constructor
    ListV2(const ListV2 &that):m_curAlloc(rebindeAllocator(that.m_curAlloc)){
        head =  m_curAlloc.allocate(1);
        m_curAlloc.construct(head,ListV2Node<T>(that.head->elem,nullptr));
        tail = head;
        auto tmp = that.head->next;
        while(tmp != nullptr){
            auto newNode = m_curAlloc.allocate(1);
            m_curAlloc.construct(newNode,ListV2Node<T>(tmp->elem,nullptr));
            tail->next = newNode;
            tail = newNode;
            tmp = tmp->next;
        };
    }

    // move constructor
    ListV2(ListV2 &&that):m_curAlloc(rebindeAllocator(that.m_curAlloc)){
        head = that.head;
        tail = that.tail;
        // no head, no tail - all between can be used without nullptring that... elemnts
        that.head = nullptr;
        that.tail = nullptr;
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

    iterator begin() {return ListV2_iterator<T>(head);}
    iterator end()   {return ListV2_iterator<T>(nullptr);}


    bool empty() const {return head == nullptr;}


    void push_back(T& elem){
        auto newNode = m_curAlloc.allocate(1);
        m_curAlloc.construct(newNode,ListV2Node<T>(elem,nullptr));
        if(head == nullptr){
            head = newNode;
        }else{
            tail->next = newNode;
        }
        tail = newNode;
    }



private:
    rebindeAllocator  m_curAlloc;
    ListV2Node<T>     *head, *tail;
};

#endif // LISTV2_H
