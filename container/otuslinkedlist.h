#ifndef OTUSLINKEDLIST_H
#define OTUSLINKEDLIST_H

#include <iostream>
#include <memory>

template <class T,
          class Allocator = std::allocator<T>
          >
class  OtusLinkeList {
    using allocator_type    = Allocator;
    using value_type        = typename allocator_type::value_type;
    using reference         = typename allocator_type::reference;
    using pointer           = typename allocator_type::pointer;
    using const_reference   = typename allocator_type::const_reference;
    using size_type         = typename allocator_type::size_type;
    using iterator          = typename allocator_type::pointer;

public:
    // constructor destructor section
    OtusLinkeList(allocator_type alloc ={}):m_alloc(alloc),cur_pos(0)
    {
        m_pnt = m_alloc.allocate(1);
        std::cout << __PRETTY_FUNCTION__ <<" 1 allocate " <<  std::endl;
    }

    void append(T someT){
        std::cout << __PRETTY_FUNCTION__<<" norm "<<cur_pos<<" : "<<m_alloc.max_size() << std::endl;
        auto tmp = m_alloc.allocate(1);
        m_alloc.construct(tmp,someT);
        cur_pos+= sizeof(size_type);

    }


    T last(){
        return *(m_pnt+cur_pos-sizeof(size_type));
    }

    iterator begin()
    {
        return m_pnt;
    }

    iterator end(){
        return (m_pnt+cur_pos);
    }

    OtusLinkeList(const OtusLinkeList&){
        std::cout << __PRETTY_FUNCTION__ <<" 2 allocate "<< std::endl;
    }

    OtusLinkeList(const OtusLinkeList&& a)noexcept{
        std::cout << __PRETTY_FUNCTION__ <<" 3 allocate "<< std::endl;
    }

    ~OtusLinkeList(){
        m_alloc.destroy(m_pnt);
        m_alloc.deallocate(m_pnt,sizeof(size_type));

    }

private:
    allocator_type  m_alloc;
    pointer         m_pnt;
    size_type       cur_pos;


};
#endif // OTUSLINKEDLIST_H
