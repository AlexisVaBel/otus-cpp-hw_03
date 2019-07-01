mkdir ./build
cd ./build
cmake ..
make -j4
#./allocator
ltrace -e malloc -e free ./allocator
#ltrace -e malloc -e free ./allocator > /dev/null
#valgrind  ./allocator 
#valgrind --tool=memcheck  ./allocator 
#valgrind --leak-check=full -v  ./allocator
