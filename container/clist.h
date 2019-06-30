#ifndef CLIST_H
#define CLIST_H

#include <memory>

#include <iostream>


template <class T>
class ListNode{
public:    
    T value;
    ListNode *next = nullptr;    
    ListNode *prev = nullptr;
};


// container
template <class T, class Allocator = std::allocator<T> >
class CList{

public:
    using  value_type           = T;

    using  reference            = value_type&;
    using  const_reference      = const value_type&;
    using  allocator_type       = Allocator;
    using  pointer              = typename std::allocator_traits<allocator_type>::pointer;
    using  const_pointer        = typename std::allocator_traits<allocator_type>::const_pointer;

    using  rebindeAllocator     = typename std::allocator_traits<allocator_type>::template rebind_alloc<ListNode<T>>;
    using  size_type            = typename allocator_type::size_type;



// construcors
    explicit    CList(rebindeAllocator alloc = {}):
        m_curAlloc(rebindeAllocator(alloc)),m_size(0),m_capacity(1),m_headNode(nullptr),m_curNode(nullptr)
    {

    }

    explicit    CList(size_type n):
        m_curAlloc(rebindeAllocator(std::allocator<T>())),m_size(0),m_capacity(1),m_headNode(nullptr),m_curNode(nullptr)

    {        

    }

    CList(size_type n, const T& value,allocator_type alloc = {}):
        m_curAlloc(rebindeAllocator(alloc)),m_size(0),m_capacity(1),m_headNode(nullptr),m_curNode(nullptr)
    {

    }

    //copy
    CList(CList &lst)
    {
        m_curAlloc = lst.get_allocator();
        m_headNode = lst.m_headNode;
        m_size     = lst.m_size;
        m_capacity = lst.m_capacity;
    }
    //move
    CList(CList &&lst)
    {
        std::swap(m_curAlloc,lst.m_curAlloc);
        std::swap(m_headNode,lst.m_headNode);
        std::swap(m_size,lst.m_size);
        std::swap(m_capacity,lst.m_capacity);
    }

    ~CList()
    {        
        auto tmp = m_headNode;
        while(tmp != nullptr){
            auto next = tmp->next;
            // if something goes wrong we got undeallocate space (
            m_curAlloc.destroy(tmp);
            m_curAlloc.deallocate(tmp,1);            
            // if something goes wrong we got undeallocate space (
            tmp = next;
        }

    }
//~construcors

    allocator_type get_allocator() const noexcept{
        return  m_curAlloc;
    }    

// ~access

// mutators
    void push_front(const T& x){        
        auto tmp = m_curAlloc.allocate(1);
        m_curAlloc.construct(tmp,ListNode<T>{x,nullptr});
        if(m_headNode == nullptr){
            m_headNode = tmp;
            m_curNode  = m_headNode;
       }else {
            m_curNode->next = tmp;
            auto       tmp2 = m_curNode;
            m_curNode       = tmp;
            m_curNode->prev = tmp2;
        };
        ++m_size;
    };

    void push_front(T&& x){        
        auto tmp = m_curAlloc.allocate(1);
        m_curAlloc.construct(tmp,ListNode<T>{x,nullptr});
        if(m_headNode == nullptr){
            m_headNode = tmp;
            m_curNode  = m_headNode;
        }else {
            m_curNode->next = tmp;
            auto       tmp2 = m_curNode;
            m_curNode       = tmp;
            m_curNode->prev = tmp2;
        };
        ++m_size;
    };

    void pop_front(){
        if(m_curNode != nullptr && m_curNode->prev != nullptr){
            auto prev = m_curNode->prev;
            prev->next = nullptr;
            m_curAlloc.destroy(m_curNode);
            m_curAlloc.deallocate(m_curNode,1);
            m_curNode = prev;
        };

    }

//~ mutators
    T  getTop(){
        return m_curNode->value;
    }

private:
    void addToNext(ListNode<T> *target,ListNode<T>* tmp){
        if(target->next != nullptr) addToNext(target->next,tmp);
        else {
            target->next = tmp;
            target       = tmp;
            ++m_size;
        }
    }

private:
    rebindeAllocator  m_curAlloc;

// don`t know for what to use size and capacity....
    size_type         m_size;
    size_type         m_capacity;
//~ don`t know for what to use size and capacity....


    ListNode<T>       *m_headNode;
    ListNode<T>       *m_curNode;
};
//~ container
#endif // CLIST_H
