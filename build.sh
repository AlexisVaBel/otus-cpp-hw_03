mkdir ./build
cd ./build
cmake ..
make -j4
#echo "starting tests"
ltrace -e malloc -e free ./allocator > /dev/null
#./ip_filter_test
