#ifndef OTUS_MAP_H
#define OTUS_MAP_H

#include <memory>
#include <functional>


template <typename Key, typename MappedT>
class Otus_map_iterator
{
private:
    using key_type      = Key;
    using mapped_type   = MappedT;
    using self          = Otus_map_iterator<key_type, mapped_type>;

public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type        = std::pair<const key_type, mapped_type>;
    using difference_type   = std::ptrdiff_t;
    using pointer           = value_type*;
    using reference         = value_type&;
};




template <
        class Key, class T, class Compare = std::less<Key>,
        class Allocator = std::allocator<std::pair<const Key, T>>
        >
class Otus_map{

public:
    using key_type                  = Key;
    using mapped_type               = T;
    using value_type                = std::pair<const key_type, mapped_type>;
    using size_type                 = std::size_t;
    using allocator_type            = Allocator;
    using reference                 = mapped_type&;
    using const_reference           = const mapped_type&;
    using pointer                   = typename std::allocator_traits<allocator_type>::pointer;
    using const_pointer             = typename std::allocator_traits<allocator_type>::const_pointer;

    using iterator                  = Otus_map_iterator<key_type,  mapped_type>;
    using const_iterator            = Otus_map_iterator<key_type,  mapped_type>;
    using reverse_iterator          = std::reverse_iterator<iterator>;
    using const_reverse_iterator    = std::reverse_iterator<const_iterator>;

    //constructors , assignment and destructor

//    `Otus_map<int, int, std::less<int>, std::allocator<std::pair<int const, int> > >
//    ::Otus_map(std::allocator<std::pair<int const, int> > const&)'



    explicit Otus_map(const allocator_type& a = allocator_type());
//    explicit Otus_map( const allocator_type& alloc );
    Otus_map(const Otus_map&)   = default;
    Otus_map(Otus_map&&)        = default;
    Otus_map(std::initializer_list<value_type> il, const allocator_type& a = allocator_type());

    template <typename FwdIterT>
    Otus_map(FwdIterT first, FwdIterT last, const allocator_type& a = allocator_type());

    Otus_map& operator= (const Otus_map&)   = default;
    Otus_map& operator= (Otus_map&&)        = default;


    ~Otus_map() = default;
    //~constructors , assignment and destructor

    // Selectors
        const_iterator      find(const key_type& key) const;
        size_type           size() const;
        size_type           max_size() const;
        bool                empty() const;
        reference           at(const key_type& key);
        const_reference     at(const key_type& key) const;
    //~Selectors

    // Mutators
        iterator            find(const key_type& key);
        std::pair<iterator, bool> insert(const key_type& key, const mapped_type& value);
        std::pair<iterator, bool> insert(const value_type& value);
        iterator            insert(const_iterator hint, const value_type& value);
        reference operator[] (const key_type& key);
        void                erase(const key_type& key);
        iterator            erase(iterator pos);
        void                clear();
     //~ Mutators

     // Iterators
        iterator            begin();
        const_iterator      begin() const;
        const_iterator      cbegin()const;
        iterator            end();
        const_iterator      end()   const;
        const_iterator      cend()  const;
        reverse_iterator    rbegin();
        reverse_iterator    rend();

        const_reverse_iterator rend()    const;
        const_reverse_iterator crend()   const;
        const_reverse_iterator rbegin()  const;
        const_reverse_iterator crbegin() const;
     //~ Iterators
private:

};


#endif // OTUS_MAP_H
