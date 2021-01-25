make d1
make gen
make d_nb
for (( i = 0; ; i++ )); do
    ./gen > d1.in || break
    ./d1 < d1.in > ans || break
    ./d_nb < d1.in | head -n 1 > ans_r || break
    head -n 1 ans > ans_heded
    diff ans_r ans_heded || break
    echo -n "."
done