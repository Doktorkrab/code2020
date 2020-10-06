make d2
make k
make gen

for ((i = 1; ; i++)) ; do 
    ./gen > test || break
    ./d2 < test > d_ans || break
    ./k < test > k_ans || break
    diff d_ans k_ans || break
    echo -n '.'
done
echo
