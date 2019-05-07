#ifndef ALLOCATORFOROTUS_H
#define ALLOCATORFOROTUS_H

#include <iostream>

template <typename U>
class AllocatorChunks{
public:
    ~AllocatorChunks(){
        if(m_prev)
            delete m_prev;
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

    ~AllocatorForOtus() _GLIBCXX_USE_NOEXCEPT {
        delete m_currentChunk;
    }

    T *allocate(std::size_t n) {

        // Allocated ones proportional to CNT_RESERVE

        if(bPassed && (m_iConstructed >= m_szLimit) ){
            bPassed = false;
            AllocatorChunks<value_type> * nextChunk =new AllocatorChunks<value_type>();
            nextChunk->m_prev = m_currentChunk;
            m_currentChunk = nextChunk;            
        }
        if(!bPassed){
            bPassed = true;
            if(m_currentChunk == nullptr){
                m_currentChunk = new AllocatorChunks<value_type>();
            }            
            m_iConstructed = 0;
            m_szStep = n * sizeof(value_type);
            m_szLimit = m_szStep * CNT_RESERVE;


            auto p = std::malloc((value_type) (m_szStep * CNT_RESERVE));
            if (!p)
                throw std::bad_alloc();

            m_currentChunk->pnt =  reinterpret_cast<pointer>(p);

            return m_currentChunk->pnt;
        }
        //~ Allocated ones proportional to CNT_RESERVE

        m_iConstructed+= m_szStep;        
        return m_currentChunk->pnt+m_iConstructed;
    }


    void deallocate(T *p, std::size_t n)
    {
        if(!bDestroyed){            
            bDestroyed = true;
            delete m_currentChunk;
        }
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args)
    {
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p) {        
        // can destroy data, while already have no rules for that space??? , if its ok?
        p->~T();
    }

private:
    bool bPassed;
    bool bDestroyed;
    int m_iConstructed;
    size_type m_szStep;
    size_type m_szLimit;

    AllocatorChunks<value_type> *m_currentChunk;

};


#endif // ALLOCATORFOROTUS_H
