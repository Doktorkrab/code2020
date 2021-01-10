make c_19
make c
make gen


for (( i = 0; ; i++ )); do
    ./gen > test || break
    (./c < test  > fast) || break
    (./c_19 < test > slow) || break
    diff fast slow || break
    echo -n '.'
done
echo