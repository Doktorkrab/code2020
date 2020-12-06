make gen
make b_11
make b
for (( i = 0; ; i++ )); do
    ./gen > test || break
    ./b_11 < test > slow || break
    ./b < test > fast || break
    diff slow fast || break
    echo -n '.'
done
echo