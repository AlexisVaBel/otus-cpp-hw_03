#ifndef ALLOCATORPULL_H
#define ALLOCATORPULL_H

#include <memory>
#include <iostream>


template <typename T>
class PullChunk{
    using value_type          = T;
    using pointer             = value_type*;
    using size_type           = std::size_t;

public:
    ~PullChunk(){
        delete m_next;
        m_next = nullptr;
        delete m_pnt; //
    }

    size_type m_szLimit;
    size_type m_szStep;

    size_type m_szNextStep;

    pointer m_pnt;
    PullChunk<value_type> *m_next;
};



template <typename T, std::size_t CNT_RESERVE>
class AllocatorPull{
public:
    using value_type          = T;
    using pointer             = value_type*;
    using const_pointer       = const value_type*;
    using reference           = value_type&;
    using const_reference     = const value_type&;
    using size_type           = std::size_t;


public:

    template<typename U>
    struct rebind {
        typedef AllocatorPull<U,CNT_RESERVE> other;
    };

    ~AllocatorPull() noexcept {
        delete m_baseChunk;
    }

    pointer allocate(std::size_t n)
    {
        if(m_baseChunk == nullptr){
            m_baseChunk               = new PullChunk<value_type>();
            m_baseChunk->m_next       = nullptr;
            m_baseChunk->m_szStep     = n * sizeof(value_type);
            m_baseChunk->m_szLimit    = n * sizeof(value_type) * CNT_RESERVE;
            m_baseChunk->m_szNextStep = 0;
            auto p = std::malloc(m_baseChunk->m_szLimit);
            if (!p)
                throw std::bad_alloc();
            m_baseChunk->m_pnt = reinterpret_cast<pointer>(p);
            m_curChunk = m_baseChunk;
        };
        if(m_curChunk->m_szNextStep > m_curChunk->m_szLimit){
            auto tmpNext = new PullChunk<value_type>();
            tmpNext->m_szNextStep = 0;
            tmpNext->m_szStep     = n * sizeof(value_type);
            tmpNext->m_szLimit    = n * sizeof(value_type) * CNT_RESERVE;
            auto p = std::malloc(tmpNext->m_szLimit);
            if (!p)
                throw std::bad_alloc();
            tmpNext->m_pnt = reinterpret_cast<pointer>(p);

            m_curChunk->m_next = tmpNext;
            m_curChunk = tmpNext;
        }else
            m_curChunk->m_szNextStep = m_curChunk->m_szNextStep + m_curChunk->m_szStep;
        return m_curChunk->m_pnt + m_curChunk->m_szNextStep;        
    }

    void deallocate(T *p, std::size_t n)
    {
//        std::cout << __PRETTY_FUNCTION__<< std::endl;
//       not freeing here, maybe mark chunk is free
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args)
    {
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p) {
//        std::cout << __PRETTY_FUNCTION__<< std::endl;
        p->~T();
    }

private:    

    PullChunk<value_type> *m_baseChunk;
    PullChunk<value_type> *m_curChunk;

};

#endif // ALLOCATORPULL_H
