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

    template<typename U>
    struct rebind {
        typedef AllocatorPull<U,CNT_RESERVE> other;
    };

    pointer allocate(std::size_t n)
    {
        if(m_pnt == nullptr || m_szCurStep >= m_szLimit){
            m_szLimit = n * sizeof (value_type) * CNT_RESERVE + sizeof (value_type);
            m_szCurStep = 0;
            auto p = std::malloc(m_szLimit);
            if (!p)
                throw std::bad_alloc();
            m_pnt = reinterpret_cast<pointer>(p);
//            std::cout << __PRETTY_FUNCTION__ << " arranged "<<m_szLimit <<std::endl;
        }else{
            m_szCurStep+= n * sizeof (value_type);
        }
//        std::cout << __PRETTY_FUNCTION__ << " "<<m_szCurStep<<std::endl;
        return reinterpret_cast<pointer> (m_pnt + m_szCurStep);

    }

    void deallocate(T *p, std::size_t n)
    {
//        std::cout << __PRETTY_FUNCTION__ << " "<<m_szCurStep<<std::endl;
        if(m_szCurStep <= 0) {
            delete m_pnt;
            m_pnt = nullptr;
        }
        else
            m_szCurStep -= n * sizeof (T);

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
};

#endif // ALLOCATORPULL_H
