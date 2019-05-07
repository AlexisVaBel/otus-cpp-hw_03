#ifndef OTUS_VECTOR_H
#define OTUS_VECTOR_H

#include <iostream>

#include <memory>
#include <functional>

//ƒЋя контейнера: методы дл€ добавлени€ элементов,
//                дл€ аллокатора воспроизвести идеальную передачу дл€ сконструировани€ объекта.
// подумать о перемещении и копировании в структуре данных

const int MIN_VCT_SIZE = 1;

template <class T,
          class Allocator = std::allocator<T>
          >
class  OtusVector {
public:
// types
    using allocator_type    = Allocator;
    using value_type        = typename allocator_type::value_type;
    using reference         = typename allocator_type::reference;
    using pointer           = typename allocator_type::pointer;
    using const_reference   = typename allocator_type::const_reference;
    using difference_type   = typename allocator_type::difference_type;
    using size_type         = typename allocator_type::size_type;
    using iterator          = typename allocator_type::pointer;
//~ types


// constructor destructor section
    OtusVector(std::size_t capacity, allocator_type alloc ={}): m_size(0), m_capacity(capacity+MIN_VCT_SIZE), m_alloc(alloc)
      , m_data(alloc.allocate(capacity+MIN_VCT_SIZE)){
    }


    OtusVector(allocator_type alloc = {}): m_size(0),  m_capacity(MIN_VCT_SIZE), m_alloc(alloc)
      , m_data(alloc.allocate(MIN_VCT_SIZE)){
    }

    OtusVector(const OtusVector&){
//        std::cout << __PRETTY_FUNCTION__ <<" 3 allocate "<<m_data<< std::endl;
    }

    OtusVector(const OtusVector&& a)noexcept{

    }

    ~OtusVector(){
        m_alloc.deallocate(m_data,m_size);
        m_alloc.~Allocator();
    }


    OtusVector& operator=(const OtusVector&){
        //todo
    }
//~ constructor destructor section

    bool operator==(const OtusVector&) const{
        //todo
    }
    bool operator!=(const OtusVector&) const{
        //todo
    }

    iterator begin(){
        return m_data;
    }

    iterator end(){
        return m_data+m_size;
    }

    void swap(OtusVector&);
    size_type size() const {
        return m_size;
    }

    size_type max_size() const{
        return m_capacity;
    }
    bool empty() const{
        return m_size == 0;
    }

    allocator_type get_allocator() const{
        return m_alloc;
    }


    void push_back(T &&t){
        if(m_size >= m_capacity){
            std::cout << __PRETTY_FUNCTION__<<std::endl;
            m_capacity +=m_size;
            resize(m_capacity);
        };
        (m_data[m_size]) = (std::forward<T> (t));
        ++m_size;
    }

    void resize(size_type szNew){
        // todo need to think about resizing
        T *tmp_data(m_alloc.allocate(szNew));
        std::copy(m_data,m_data+m_size,tmp_data);
        m_alloc.deallocate(m_data,m_size);
        m_data = tmp_data;
    }


private:
    size_type m_size;
    size_type m_capacity;
    allocator_type m_alloc;
    T *m_data;

};
#endif // OTUS_VECTOR_H
