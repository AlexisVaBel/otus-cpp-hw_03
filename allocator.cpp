#include <iostream>
#include <vector>
#include <map>

#include "container/arraylist.h"
#include "container/otuslinkedlist.h"
#include "allocs/allocatorpull.h"



int main(int, char *[]) {

    uint upper_bound = 5;

    auto lst = new OtusLinkeList<int, AllocatorPull<int,10>>();
//    auto lst = new OtusLinkeList<int>();
    lst->append(10);
    lst->append(11);
    lst->append(12);


    for(auto it = lst->begin();it < lst->end(); it = it + sizeof(*it)){
        std::cout << *it << " ";
    }
    delete  lst;

//    auto alst =new otus_container::ArrayList<int,AllocatorPull<int,10>>();
//    for (size_t i = 0; i < upper_bound; ++i) {
//        alst->add(i);
//    }

//    for (size_t i = 0; i < upper_bound; ++i) {
//        std::cout<< alst->at(i) << " ";
//    }
//    std::cout << std::endl;
//    delete alst;

//    auto m = std::map<int, int, std::less<int>, AllocatorPull<std::pair<const int, int>,10>>();
//    auto m = std::map<int, int>{};


//    for (size_t i = 0; i < upper_bound; ++i) {
//        m[i] = i;
//    }
//    std::cout<<"============= get total ============="<< std::endl;
//    for (size_t i = 0; i < upper_bound; ++i) {

//        std::cout << m.at(i)<< " ";
//    }


    return 0;
}


//https://medium.com/@vgasparyan1995/how-to-write-an-stl-compatible-container-fc5b994462c6
