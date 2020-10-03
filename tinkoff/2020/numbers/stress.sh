make d
make d1
make gen

for ((i = 1; ; i++)) ; do 
    ./gen > test || break
    ./d < test > d_ans || break
    ./d1 < test > d1_ans || break
    diff d_ans d1_ans || break
    echo -n '.'
done
echo
