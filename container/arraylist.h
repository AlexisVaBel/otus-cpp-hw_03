#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>
#include <memory>

namespace otus_container{
/*
 * Implementing concpetion of java`s ArrayList
 * resizable indexed array
 *  initiated with fixed size
 *  on deleting item just emptyin element
 *  on adding item if over size, than allocating another portion of data
*/


    static int  ARRLST_DEFAULT_LNG = 10;

//    template <class T>
//    class ARR_LST_TAIL{
//        // base element gets index 0, next 1
//        // item position counts as m_curIndex*ARRLST_DEFAULT_LNG + i
//        size_t          m_curIndex;
//        ARR_LST_TAIL<T> m_next;
//    };



    template <class T,
              class Allocator = std::allocator<T>
              >
    class  ArrayList {
        using allocator_type    = Allocator;
        using value_type        = typename allocator_type::value_type;
        using reference         = typename allocator_type::reference;
        using pointer           = typename allocator_type::pointer;
        using const_reference   = typename allocator_type::const_reference;
        using size_type         = typename allocator_type::size_type;
        using iterator          = typename allocator_type::pointer;

    public:
        // constructor destructor section
        ArrayList(std::size_t capacity, allocator_type alloc ={}): m_size(0), m_capacity(capacity > ARRLST_DEFAULT_LNG ? capacity : ARRLST_DEFAULT_LNG ), m_alloc(alloc)
        {
            m_pointer = m_alloc.allocate(m_capacity);
        }


        ArrayList(allocator_type alloc = {}): m_size(0),  m_capacity(ARRLST_DEFAULT_LNG), m_alloc(alloc)
        {
            m_pointer = m_alloc.allocate(m_capacity);
        }

        ArrayList(const ArrayList&){
            //        std::cout << __PRETTY_FUNCTION__ <<" 3 allocate "<<m_data<< std::endl;
        }

        ArrayList(const ArrayList&& a)noexcept{
            //        std::cout << __PRETTY_FUNCTION__ <<" 3 allocate "<<m_data<< std::endl;
        }

        ~ArrayList(){
            m_alloc.~Allocator();
//            If this is a null-pointer, the function does nothing.
            delete m_pointer;
        }


        ArrayList& operator=(const ArrayList&){
            //todo
        }
        //~ constructor destructor section

        void add (value_type someValue)
        {
            std::cout<< someValue << " - capacity:position "<< m_capacity<<" "<<m_size <<std::endl;
            if(m_size < m_capacity){
                m_alloc.construct(m_pointer+m_size,someValue);
                m_size++;
            }
        }

        value_type at(size_t pos){
            if(pos < m_size)
                return  *(m_pointer+pos);
            else return  0;
        }



        void add (size_t pos,value_type someValue)
        {

        }


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


    private:
        size_type m_size;
        size_type m_capacity;
        allocator_type m_alloc;

        pointer     m_pointer;

    };
}

#endif // ARRAYLIST_H
