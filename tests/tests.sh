lfu_cache_obj="./build/lfu_cache.o"
ideal_cache_odj="./build/ideal_cache.o"

little_test_folder="./tests/little_tests/"
little_test_files_names=("t1.dat" "t2.dat" "t3.dat" "t4.dat" "t5.dat" "t6.dat" "t7.dat" "t8.dat" "t9.dat" "t10.dat")

lfu_little_ans=(4 4 3 1 13 18 2 1 9 7)
ideal_little_ans=(4 7 8 3 13 24 3 3 11 10)

big_test_folder="./tests/big_tests/"
big_test_files_names=("010.dat" "011.dat" "015.dat" "t1.dat" "t2.dat" "t3.dat" "t4.dat")

echo "little tests:"
echo
for i in ${!little_test_files_names[@]}; do
    echo ${little_test_files_names[$i]}
    ${lfu_cache_obj} <  ${little_test_folder}${little_test_files_names[$i]}
    echo LFU correct = ${lfu_little_ans[$i]}
    ${ideal_cache_odj} < ${little_test_folder}${little_test_files_names[$i]}
    echo Ideal correct = ${ideal_little_ans[$i]}
    echo
done

echo "big tests:"
echo
for t in ${big_test_files_names[@]}; do
    echo $t
    ${lfu_cache_obj} < ${big_test_folder}${t}
    ${ideal_cache_odj} < ${big_test_folder}${t}
    echo
done
