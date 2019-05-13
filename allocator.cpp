#include <iostream>
#include <vector>
#include <map>
#include "allocatorforotus.h"
#include "allocs/allocatorpull.h"
#include "otus_map.h"
#include "otus_vector.h"

int main(int, char *[]) {

    uint upper_bound = 10;
//    auto vct = OtusVector<int,AllocatorForOtus<int,4>>();
//    auto vct = OtusVector<int>();


//    vct.begin();
//    std::cout<< vct.end() <<std::endl;
//    for (size_t i = 0; i < upper_bound; ++i) {
//        vct.push_back(i);
//    }
//    for(auto i = vct.begin(); i< vct.end(); ++i){
//        std::cout<< *i <<std::endl;
//    }







//    auto m = std::map<int, int, std::less<int>, AllocatorForOtus<std::pair<const int, int>,10>>();
    auto m = std::map<int, int, std::less<int>, AllocatorPull<std::pair<const int, int>,10>>();
//    auto m = std::map<int, int>{};


    for (size_t i = 0; i < upper_bound; ++i) {
        m[i] = i;        
    }
    std::cout<<"============= get total ============="<< std::endl;
    for (size_t i = 0; i < upper_bound; ++i) {

        std::cout << m.at(i)<< " ";
    }

    return 0;
}


//https://medium.com/@vgasparyan1995/how-to-write-an-stl-compatible-container-fc5b994462c6
