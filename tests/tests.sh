lfu_cache_obj="./build/lfu_cache/lfu_cache.o"
ideal_cache_odj="./build/ideal_cache/ideal_cache.o"
test_folder="./tests/"
test_files_names=("010.dat" "011.dat" "015.dat" "t1.dat" "t2.dat" "t3.dat" "t4.dat")

for t in ${test_files_names[@]}; do
    echo $t
    ${lfu_cache_obj} < ${test_folder}${t}
    ${ideal_cache_odj} < ${test_folder}${t}
    echo
done
