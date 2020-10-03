make e_unique
make e_stress
make gen

for ((i = 1; ; i++)) ; do 
    ./gen > test || break
    ./e_unique < test > eq_ans || break
    ./e_stress < test > ee_ans || break
    diff eq_ans ee_ans || break
    echo -n '.'
done
echo
