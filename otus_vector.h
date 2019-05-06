#ifndef OTUS_VECTOR_H
#define OTUS_VECTOR_H

#include <iostream>

#include <memory>
#include <functional>

const int MIN_VCT_SIZE = 4;

template <class T,
          class Allocator = std::allocator<T>
          >
class  OtusVector {
public:
    using allocator_type    = Allocator;
    using iterator          = T*;
    using reference         = T&;
    using pointer           = typename std::allocator_traits<allocator_type>::pointer;


/*
    explicit vector (const allocator_type& alloc = allocator_type());

    explicit vector (size_type n);
             vector (size_type n, const value_type& val,
                     const allocator_type& alloc = allocator_type());
*/
    explicit OtusVector (const allocator_type& alloc = allocator_type()){

    }

    OtusVector(): m_array(new T[MIN_VCT_SIZE]),reserved_size(MIN_VCT_SIZE), size(0){

    }

    OtusVector(int n): m_array(new T[n]),reserved_size(n + MIN_VCT_SIZE), size(0){}

    ~OtusVector() {
        delete[] m_array;
    }


    template<typename ... Args> reference emplace_back(Args&&... args);



    pointer allocate(size_t n){
        std::allocator_traits<allocator_type> _Tr;
//        _Tr::allocate();
    }


    void push_back(const T &t)
    {
        if(size == reserved_size)
            resize(reserved_size + MIN_VCT_SIZE);

        m_array[size] = t;
        size++;
    }

    void resize(int n)
    {
        if(n > reserved_size)
        {
            auto new_array(new T[n]);
            std::copy ( m_array, m_array+size, new_array);
            delete [] m_array;
            m_array = new_array;
            reserved_size = n;  // increasing size;
        }
    }



    iterator begin()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return m_array;
    }


    iterator end()
    {
        std::cout << __PRETTY_FUNCTION__ <<" size is " << reserved_size << std::endl;
        return m_array + size;
    }

private:
    T * m_array;

    allocator_type  *m_alloc;
    int size;
    int reserved_size;
};
#endif // OTUS_VECTOR_H
