#include <iostream>

#include <vector>
#include <map>
#include <container/clist.h>
#include <container/listv2.h>

#include <alloc/allocatorpull.h>

static int const I_ELM_CNT = 9;
static int const I_ELM_ALLOC = 10;

// some functional works ))
template <int ival>
struct Factorial{
    static const int ifact = Factorial<ival - 1>::ifact * ival;
};

template<>
struct Factorial<0>{
    static const int ifact = 1;
};



template<int ival, class T, class ... Args>
struct Cyclce_Map{
    static void produceFact(std::map<T,Args ...> &map){
        map[ival]=Factorial<ival>::ifact;
        Cyclce_Map<ival-1,T,Args...>::produceFact(map);
    }
};


template<class T, class ... Args>
struct Cyclce_Map<0,T,Args ...>{
    static void produceFact(std::map<T,Args ...> &map){
        map[0]=Factorial<0>::ifact;
    }
};
// some functional works ))



template <class T, class ... Args>
void it_print_lst_value(ListV2<T,Args ...> &lst){
    auto itBegin = lst.begin();
    auto itEnd   = lst.end();
    while(itBegin != itEnd){
        std::cout <<(*itBegin) << std::endl;
        ++itBegin;
    }
}


int main(int, char *[]) {
    // maps
    std::map <int, int> std_alloc_map;
    std::map <int, int,std::less<int>, AllocatorPull<std::pair<const int, int>,I_ELM_ALLOC>> cust_alloc_map;

    Cyclce_Map<I_ELM_CNT,int,int>::produceFact(std_alloc_map);
    Cyclce_Map<I_ELM_CNT,int,int,std::less<int>, AllocatorPull<std::pair<const int, int>,I_ELM_ALLOC>>::produceFact(cust_alloc_map);

    for(auto k: std_alloc_map){
        std::cout << k.first << " " << k.second << std::endl;
    }

    for(auto k: cust_alloc_map){
        std::cout << k.first << " " << k.second << std::endl;
    }

    // lists
    ListV2<int> std_alloc_lst;
    ListV2<int,AllocatorPull<int,I_ELM_ALLOC>> cust_alloc_lst;
    for(int i=0; i<= I_ELM_CNT; ++i){
        std_alloc_lst.push_back(i);
        cust_alloc_lst.push_back(i);
    }

    it_print_lst_value(std_alloc_lst);
    it_print_lst_value(cust_alloc_lst);

    return 0;
}



