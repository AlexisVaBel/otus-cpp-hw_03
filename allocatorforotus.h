#ifndef ALLOCATORFOROTUS_H
#define ALLOCATORFOROTUS_H

#include <iostream>

template <typename U>
class AllocatorChunks{
public:
    ~AllocatorChunks(){
        delete m_prev;
        std::cout << __PRETTY_FUNCTION__ << "[pnt = "  << "]" <<pnt<< std::endl;
        std::free(pnt);
    }
    AllocatorChunks<U> *m_prev;
    U *pnt;
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

        // Allocated ones proportional to CNT_RESERVE

        if(bPassed && (m_iConstructed >= m_szLimit) ){
            std::cout << "over limit "<< m_szLimit << " actual: "<<m_iConstructed*m_szStep<< std::endl;
            bPassed = false;
            AllocatorChunks<T> * nextChunk =new AllocatorChunks<T>();
            nextChunk->m_prev = m_currentChunk;
            m_currentChunk = nextChunk;
        }
        if(!bPassed){
            bPassed = true;
            if(m_currentChunk == nullptr){
                m_currentChunk = new AllocatorChunks<T>();
            }

            m_iConstructed = 0;
            m_szStep = n * sizeof(T);
            m_szLimit = m_szStep * CNT_RESERVE;
            std::cout << __PRETTY_FUNCTION__ << " with limit "<< m_szLimit << std::endl;

            auto p = std::malloc(m_szStep * CNT_RESERVE);
            if (!p)
                throw std::bad_alloc();

            m_currentChunk->pnt =  reinterpret_cast<T *>(p);

            std::cout << m_currentChunk->pnt << std::endl;
            return m_currentChunk->pnt;
        }

        m_iConstructed+= m_szStep;
        std::cout << m_currentChunk->pnt +m_iConstructed<< std::endl;
        return m_currentChunk->pnt+m_iConstructed;
    }


    void deallocate(T *p, std::size_t n) {
        if(!bDestroyed){
            std::cout << __PRETTY_FUNCTION__ << std::endl;
            bDestroyed = true;
            delete m_currentChunk;
        }
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;       
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p) {        
        // can destroy data, while already have no rules for that space??? need to ask question for Dmitr
        std::cout << __PRETTY_FUNCTION__ <<" pnt "<<p<< std::endl;
        p->~T();
    }

private:
    bool bPassed;
    bool bDestroyed;
    int m_iConstructed;
    std::size_t m_szStep;
    std::size_t m_szLimit;

    AllocatorChunks<T> *m_currentChunk;

};


#endif // ALLOCATORFOROTUS_H
