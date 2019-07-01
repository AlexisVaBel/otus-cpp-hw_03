#include <iostream>

#include <map>
#include <container/clist.h>

#include <alloc/allocatorpull.h>

static int const I_ELM_CNT = 9;

// some functional works ))
template <int ival>
struct Factorial{
    static const int ifact = Factorial<ival - 1>::ifact * ival;
};

template<>
struct Factorial<0>{
    static const int ifact = 1;
};

template<int ival,class T, class ... Args>
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



int main(int, char *[]) {
    std::map <int, int> std_alloc_map;
    std::map <int, int,std::less<int>, AllocatorPull<std::pair<const int, int>,I_ELM_CNT>> cust_alloc_map;

    Cyclce_Map<I_ELM_CNT,int,int>::produceFact(std_alloc_map);
    Cyclce_Map<I_ELM_CNT,int,int,std::less<int>, AllocatorPull<std::pair<const int, int>,I_ELM_CNT>>::produceFact(cust_alloc_map);



    for(auto k: std_alloc_map){
        std::cout << k.first << " " << k.second << std::endl;
    }

    for(auto k: cust_alloc_map){
        std::cout << k.first << " " << k.second << std::endl;
    }


    CList<int,std::allocator<int>> std_alloc_lst;
    CList<int,AllocatorPull<int,I_ELM_CNT>> cust_alloc_lst;
    for(auto i=0; i<= I_ELM_CNT; ++i){
        std_alloc_lst.push_front(i);
    }
    for(auto i=0; i<= I_ELM_CNT; ++i){
        cust_alloc_lst.push_front(i);
    }

    for(auto i=0; i<= I_ELM_CNT; ++i){
        std::cout << std_alloc_lst.getTop() <<std::endl;
        std_alloc_lst.pop_front();
    }

    for(auto i=0; i<= I_ELM_CNT; ++i){
        std::cout << cust_alloc_lst.getTop() <<std::endl;
        cust_alloc_lst.pop_front();
    }



    return 0;
}



