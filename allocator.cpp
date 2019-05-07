#include <iostream>
#include <vector>
#include <map>
#include "allocatorforotus.h"
#include "otus_map.h"
#include "otus_vector.h"

int main(int, char *[]) {

    uint upper_bound = 1;
    auto vct = OtusVector<int,AllocatorForOtus<int,4>>();
//    auto vct = OtusVector<int>();


//    vct.begin();
//    std::cout<< vct.end() <<std::endl;
    for (size_t i = 0; i < upper_bound; ++i) {
        vct.push_back(i);
    }
//    for(auto i = vct.begin(); i< vct.end(); ++i){
//        std::cout<< *i <<std::endl;
//    }







//    auto m = std::map<int, int, std::less<int>, AllocatorForOtus<std::pair<const int, int>,10>>();
//    auto m = std::map<int, int>{};

//     m[0] = 1;

//    for (size_t i = 0; i < upper_bound; ++i) {
//        m[i] = i;
//        std::cout << std::endl;
//    }
//    std::cout<<"============= get total ============="<< std::endl;
//    for (size_t i = 0; i < upper_bound; ++i) {

//        std::cout << m.at(i)<< " ";
//    }
//    std::cout<<std::endl;


    return 0;
}

// -fsanitize=address (для компилятора и линкера) посреди работы будет вылетать инфа !!
// valgrind делает тоже самое valgrind --tool memory или как то так

// ИНФА из лекции GOF2 allocator;
// идеальная передача

//struct foo{
//    int a;
//    int b;
//    foo(int a_, int b_):a(a_),b(b_){};
//    foo (const &foo) = delete;
//};

//fl<foo> l;
//l.add(1,2);
//https://medium.com/@vgasparyan1995/how-to-write-an-stl-compatible-container-fc5b994462c6
