#ifndef ALLOCATORPULL_H
#define ALLOCATORPULL_H

#include <memory>
#include <iostream>

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

    AllocatorPull():m_szLimit(0),m_szCurStep(0),m_pnt(nullptr),m_pntCur(nullptr){}
    ~AllocatorPull(){
        if(m_pnt != nullptr) free(m_pnt);
    }

    template<typename U>
    struct rebind {
        typedef AllocatorPull<U,CNT_RESERVE> other;
    };

    pointer allocate(std::size_t n)
    {
        if(m_pnt == nullptr){
            auto p = std::malloc(n * sizeof (value_type)* CNT_RESERVE);
            if (!p)
                throw std::bad_alloc();
            m_pnt = reinterpret_cast<pointer>(p);
            m_pntCur = m_pnt;
        }
        return reinterpret_cast<pointer> (m_pntCur++);
    }

    void deallocate(T *p, std::size_t n)
    {


//        std::cout << __PRETTY_FUNCTION__ << " "<<m_szCurStep<<std::endl;
        if(m_pntCur == m_pnt) {
            free(m_pnt);
            m_pnt = nullptr;
        }
        else
            m_pntCur--;


    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args)
    {        
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p) {        
        p->~T();
    }

    size_type max_size(){
        return m_szLimit;
    }

private:    

    size_type m_szLimit;

    size_type m_szCurStep;

    pointer m_pnt;
    pointer m_pntCur;
};

#endif // ALLOCATORPULL_H
