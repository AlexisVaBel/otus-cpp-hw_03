#ifndef CLIST_H
#define CLIST_H

#include <memory>

#include <iostream>





template <class T>
class ListNode{
public:
    ListNode<T>(T arg1):value(arg1),next(nullptr){
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    ~ListNode(){
    }
    T value;
    ListNode<T> *next;
};


template<class T>
class ListIterator: public std::iterator<std::input_iterator_tag, ListNode<T>>
{
public:
    ListIterator(ListNode<T>* p):m_p(p){}
    ListIterator(const ListIterator &it):m_p(it.m_p){};
    ~ListIterator(){

    }

    bool operator!=(ListIterator const& other) const {
        std::cout << __PRETTY_FUNCTION__ <<std::endl;
        return (m_p != nullptr && m_p != other.m_p);}

    bool operator==(ListIterator const& other) const {return m_p == other.m_p;}
    typename ListIterator::reference operator*() const {
        return *m_p;
    }
    ListIterator& operator++() {
        if(m_p != nullptr){
            m_p = m_p->next;
        }
        return *this;
    }
private:
    ListNode<T>* m_p;
};


// container
template <class T, class Allocator = std::allocator<T> >
class CList{

public:

    using  iterator             =ListIterator<T>;
    using  const_iterator       =ListIterator<const T>;


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
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    explicit    CList(size_type n):
        m_curAlloc(rebindeAllocator(std::allocator<T>())),m_size(0),m_capacity(1),m_headNode(nullptr),m_curNode(nullptr)

    {        
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    CList(size_type n, const T& value,allocator_type alloc = {}):
        m_curAlloc(rebindeAllocator(alloc)),m_size(0),m_capacity(1),m_headNode(nullptr),m_curNode(nullptr)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    //copy
    CList(CList &lst)
    {
//        m_curAlloc = lst.get_allocator();
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
            auto toDelete = tmp;
            tmp = tmp->next;
            m_curAlloc.deallocate(toDelete,1);

        }
    }

//~construcors

    iterator begin(){
        return iterator(m_headNode);
    }
    iterator end(){
        return iterator(m_curNode->next);
    }

    allocator_type get_allocator() const noexcept{
        return  m_curAlloc;
    }

// ~access



// mutators
    void push_front(T x){
        auto tmp = m_curAlloc.allocate(1);        
        m_curAlloc.construct(tmp,ListNode<T>{x});
        if(m_curNode == nullptr){
            m_curNode= tmp;
            m_curNode->next = nullptr;
            m_headNode = m_curNode;            
        }else {
            auto tmpNode = m_curNode;
            m_curNode = tmp;
            tmpNode->next = m_curNode;
        }        
    };


    void pop_front(){
        if(m_curNode == nullptr)return;
        auto tmp    = m_headNode;
        auto preTmp = m_headNode;
        while (tmp->next != nullptr) {
            preTmp = tmp;
            tmp = tmp->next;
        };
        m_curNode = preTmp;
        m_curNode->next = nullptr;
        if(m_curNode == m_headNode && m_curNode == preTmp) {
            m_headNode = nullptr;
            m_curNode  = nullptr;
        }
        m_curAlloc.deallocate(tmp,1);
    }

//~ mutators
    T  getTop(){
        return m_curNode->value;
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
