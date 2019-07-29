#include <iostream>

#include <vector>
#include <map>
#include <container/listv2.h>
#include <alloc/allocatorpull.h>


static int const I_ELM_ALLOC = 10;

//  some functional works ))
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
// ~some functional works ))


struct hard{
 hard(const char*, size_t){}
// hard(const hard &) = delete;
  hard(const hard &&) = delete;
};



template <class T, class ... Args>
void it_print_lst_value(ListV2<T,Args ...> &lst){
    auto itBegin = lst.begin();
    auto itEnd   = lst.end();
    while(itBegin != itEnd){
        std::cout <<(*itBegin) << std::endl;
        ++itBegin;
    }
}

    using  cust_allocated_map = AllocatorPull<std::pair<const int, int>,I_ELM_ALLOC>;

int main(int, char *[]) {
    // maps
    std::map <int, int> std_alloc_map;
    std::map <int, int,std::less<int>, cust_allocated_map> cust_alloc_map;

    Cyclce_Map<I_ELM_ALLOC-1,int,int>::produceFact(std_alloc_map);
    Cyclce_Map<I_ELM_ALLOC-1,int,int,std::less<int>, cust_allocated_map>::produceFact(cust_alloc_map);

    for(auto k: std_alloc_map){
        std::cout << k.first << " " << k.second << std::endl;
    }

    for(auto k: cust_alloc_map){
        std::cout << k.first << " " << k.second << std::endl;
    }

    // lists
    ListV2<int> std_alloc_lst;
    ListV2<int,AllocatorPull<int,I_ELM_ALLOC>> cust_alloc_lst;
    for(int i=0; i<= I_ELM_ALLOC-1; ++i){
        std_alloc_lst.push_back(i);
        cust_alloc_lst.push_back(i);
    }

    it_print_lst_value(std_alloc_lst);
    it_print_lst_value(cust_alloc_lst);




    // some test cases: leaked, copy, move
//    ListV2<hard,AllocatorPull<hard,I_ELM_ALLOC>> cust_alloc_lst_hard;
//    cust_alloc_lst_hard.push_back(hard("one",1));
//    cust_alloc_lst_hard.push_back(hard("two",2));

//    ListV2<std::string> leaked_lst;
//    auto tmp = std::string(1024, 'x');
//    auto  const tmp2 = std::string(1024, 'o');
//    leaked_lst.push_back(tmp);
//    leaked_lst.push_back(tmp2);
//    leaked_lst.push_back(std::string(1024, 'y'));
//    leaked_lst.push_back(std::string(1024, 'z'));
//    leaked_lst.push_back(std::string(1024, 'l'));

//    ListV2<std::string> copy_lst = std::move(leaked_lst);
//    it_print_lst_value(copy_lst);
    //~ some test cases: leaked, copy, move
    return 0;
}



