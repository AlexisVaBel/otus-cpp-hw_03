#include <iostream>
#include <vector>
#include <map>
#include "allocatorforotus.h"

template<typename T>
struct logging_allocator {
    using value_type = T;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind {
        using other = logging_allocator<U>;
    };

    T *allocate(std::size_t n) {
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
        auto p = std::malloc(n * sizeof(T));
        if (!p)
            throw std::bad_alloc();
        return reinterpret_cast<T *>(p);
    }

    void deallocate(T *p, std::size_t n) {
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
        std::free(p);
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        p->~T();
    }
};

int main(int, char *[]) {
//    auto v = std::vector<int, AllocatorForOtus<int>>{};

//    v.reserve(5);

//    for (size_t i = 0; i < 1 /* 5 */; ++i) {
//        v.emplace_back(i);
//        std::cout << std::endl;
//    }


    auto m = std::map<int, int, std::less<int>, AllocatorForOtus<std::pair<const int, int>,10>>{};
//    auto m = std::map<int, int>{};
//    m.reserve(10);
    for (size_t i = 0; i < 5; ++i) {
        m[i] = i;
        std::cout << std::endl;
    }

    return 0;
}

// -fsanitize=address (для компилятора и линкера) посреди работы будет вылетать инфа !!
// valgrind делает тоже самое valgrind --tool memory или как то так

// ИНФА из лекции GOF2 allocator;
// идеальная передача
//ДЛЯ контейнера: методы для добавления элементов,
//                для аллокатора воспроизвести идеальную передачу для сконструирования объекта.
// подумать о перемещении и копировании в структуре данных
//struct foo{
//    int a;
//    int b;
//    foo(int a_, int b_):a(a_),b(b_){};
//    foo (const &foo) = delete;
//};

//fl<foo> l;
//l.add(1,2);
