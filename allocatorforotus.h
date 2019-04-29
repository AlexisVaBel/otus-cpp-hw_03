#ifndef ALLOCATORFOROTUS_H
#define ALLOCATORFOROTUS_H

#include <iostream>


template <typename T>
struct HoldingNode{
    ~HoldingNode(){
        free(pnt);
    }

    T * pnt;
    HoldingNode<T> *m_prevNode;
    HoldingNode<T> *m_nextNode;
};


template <typename T, std::size_t CNT_RESERVE>
class AllocatorForOtus{
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

public:        



    template<typename U>
    struct rebind {
        typedef AllocatorForOtus<U,CNT_RESERVE> other;
    };


    T *allocate(std::size_t n) {
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;        

        auto p = std::malloc(n * sizeof(T));
        if (!p)
            throw std::bad_alloc();

        return reinterpret_cast<T *>(p);
    }


    void deallocate(T *p, std::size_t n) {
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
//        std::free(p);
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
         HoldingNode<T> *tmpNode = m_baseNode;
        for(int i=0; i< CNT_RESERVE; i++){
            if( p == tmpNode->pnt){
                HoldingNode<T> *bufNode1 = tmpNode->m_nextNode;
                if(bufNode1 != nullptr && bufNode1->m_prevNode != nullptr){

                }
            }
        }
//        p->~T();
    }

private:
    HoldingNode<T> *m_baseNode;

};


#endif // ALLOCATORFOROTUS_H
