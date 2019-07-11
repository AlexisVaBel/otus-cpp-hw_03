#ifndef CLIST_H
#define CLIST_H

#include <memory>

#include <iostream>


template <class T>
class ListNode{
public:
    ListNode<T>(T arg1):value(arg1),next(nullptr),prev(nullptr){

    }

    ListNode<T>(ListNode<T> &&arg1):value(arg1.value),next(arg1.next),prev(arg1.prev){
        std::cout << __PRETTY_FUNCTION__  << std::endl;
    }

    ~ListNode(){

    }

    T value;
    ListNode<T> *next;
    ListNode<T> *prev;
};


template<class T>
class ListIterator: public std::iterator<std::input_iterator_tag, ListNode<T>>
{
public:
    ListIterator(ListNode<T>* p,int iCnt):m_p(p),m_iCnt(iCnt){
        std::cout << __PRETTY_FUNCTION__ << m_p ->value<<std::endl;
        std::cout << __PRETTY_FUNCTION__ << m_p ->prev<<std::endl;
    }
    ListIterator(const ListIterator &it):m_p(it.m_p),m_iCnt(it.m_iCnt){
        std::cout << __PRETTY_FUNCTION__ <<std::endl;
    };
    ~ListIterator(){

    }

    bool operator!=(ListIterator const& other) const {
//        std::cout << __PRETTY_FUNCTION__ <<std::endl;
        return ((m_iCnt != other.m_iCnt));}

    bool operator==(ListIterator const& other) const {return (m_iCnt == other.m_iCnt);}

    typename ListIterator::reference operator*() const {
        return *m_p;
    }
    ListIterator& operator++() {
        if(m_p != nullptr && m_p->next != nullptr){
            std::cout << __PRETTY_FUNCTION__ << std::endl;
            m_p = m_p->next;
        }
        m_iCnt++;
        return *this;
    }
private:
    int          m_iCnt;
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
        m_curAlloc(rebindeAllocator(alloc)),m_size(0),m_capacity(1),m_curNode(nullptr)
    {
//        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    explicit    CList(size_type n):
        m_curAlloc(rebindeAllocator(std::allocator<T>())),m_size(0),m_capacity(1),m_curNode(nullptr)

    {        
//        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    CList(size_type n, const T& value,allocator_type alloc = {}):
        m_curAlloc(rebindeAllocator(alloc)),m_size(0),m_capacity(1),m_curNode(nullptr)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    //copy
    CList(CList &lst)
    {
        m_curAlloc = lst.m_curAlloc;
        m_curNode = lst.m_curNode;
        m_size     = lst.m_size;
        m_capacity = lst.m_capacity;
    }
    //move
    CList(CList &&lst)
    {
        std::swap(m_curAlloc,lst.m_curAlloc);
        std::swap(m_curNode,lst.m_curNode);
        std::swap(m_size,lst.m_size);
        std::swap(m_capacity,lst.m_capacity);
    }

    ~CList()
    {
        if(m_curNode != nullptr){
            auto tmp = m_curNode;
            while(tmp != nullptr){
                auto toDelete = tmp;
                tmp = tmp->prev;
                m_curAlloc.deallocate(toDelete,1);
            }
        }
    }

//~construcors

    iterator begin(){
        auto tmpNode  = m_curNode;
        if(m_curNode == nullptr)return iterator(tmpNode,0);

        tmpNode->prev = m_curNode->prev;
        tmpNode->next = m_curNode->next;
        while(tmpNode != nullptr && tmpNode->prev != nullptr){


            if(tmpNode->prev != nullptr){
                std::cout << tmpNode << " " <<tmpNode->value<< std::endl;
                auto tmp = tmpNode;
                tmpNode  = tmpNode->prev;

            }
        }
        return iterator(tmpNode,0);
    }
    iterator end(){
        return iterator(m_curNode,m_size+1);
    }

    allocator_type get_allocator() const noexcept{
        return  m_curAlloc;
    }

// ~access



// mutators
    void push_front(T x){
        ListNode<T> *tmpNode = nullptr;
        if(m_curNode != nullptr){
            tmpNode = m_curNode;            
        };

        m_curNode = m_curAlloc.allocate(1);
        m_curAlloc.construct(m_curNode,ListNode<T>(x));

        m_curNode->prev = tmpNode;
        m_curNode->next = nullptr;

        m_size++;
    }


    void pop_front(){
        if(m_curNode == nullptr)return;
        auto nodeToRelease = m_curNode;
        m_curNode = m_curNode->prev;
        if(m_curNode != nullptr) m_curNode->next = nullptr;
        m_curAlloc.destroy(nodeToRelease);
        m_curAlloc.deallocate(nodeToRelease,1);
        m_size--;
    }

//~ mutators
    T  getTop(){
//        std::cout << __PRETTY_FUNCTION__ << m_curNode <<" of size "<< m_size << std::endl;
        return m_curNode->value;
    }

    int getSize(){
        return m_size;
    }

private:
    rebindeAllocator  m_curAlloc;
    int               m_size;
    size_type         m_capacity;

    ListNode<T>       *m_curNode;    
};
//~ container
#endif // CLIST_H
