#ifndef ALLOCATORFOROTUS_H
#define ALLOCATORFOROTUS_H

#include <iostream>


template <typename T>
struct HoldingNode{
    HoldingNode(){
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    ~HoldingNode(){
        std::cout << __PRETTY_FUNCTION__ << std::endl;
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

        // allocate at this moment
        if(m_baseNode == nullptr){
            m_baseNode = new HoldingNode<T> ();
            auto p = std::malloc(n * sizeof(T));
            if (!p)
                throw std::bad_alloc();
            m_iCurPos = 0;
            m_baseNode->pnt = reinterpret_cast<T *>(p);
        }else{


            HoldingNode<T> *m_prevNode = m_baseNode;


            for(int i=0; i< CNT_RESERVE; i++){
                HoldingNode<T> *m_tmpNode = new HoldingNode<T> ();
                auto p = std::malloc(n * sizeof(T));
                if (!p)
                    throw std::bad_alloc();
                m_tmpNode->pnt = reinterpret_cast<T *>(p);

                m_tmpNode->m_prevNode = m_prevNode;
                m_prevNode->m_nextNode = m_tmpNode;
                m_prevNode = m_tmpNode;
                //
            }

        }
        //~ allocate at this moment
        int i = 0;
        HoldingNode<T> *m_prevNode = m_baseNode;
        while( i < m_iCurPos){
            i++;
            m_prevNode = m_prevNode->m_nextNode;
        }
        m_iCurPos++;
        return m_prevNode->pnt ;
    }


    void deallocate(T *p, std::size_t n) {
        std::cout << __PRETTY_FUNCTION__ << "[n = " << m_iCurPos << "]" << std::endl;
        std::free(p);
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
                    bufNode1->m_prevNode = tmpNode->m_prevNode;
                    tmpNode->m_prevNode->m_nextNod = tmpNode;
                }
                tmpNode->~HoldingNode<T>();
            }
        }
//        p->~T();
    }

private:
    HoldingNode<T> *m_baseNode;
    int             m_iCurPos;

};


#endif // ALLOCATORFOROTUS_H
