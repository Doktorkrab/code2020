make e
make e_1
make gen
for (( i = 0; ; i++ )); do
    ./gen > test || break
    ./e < test > fast || break
    ./e_1 < test > slow || break
    diff fast slow || break
    echo -n '.'
done
echo