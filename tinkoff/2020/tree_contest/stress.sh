make gen
make a
make a_slow
for (( i = 0; ; i++ )); do
    ./gen > test || break
    ./a_slow < test > slow || break
    ./a < test > fast || break
    diff slow fast || break
    echo -n '.'
done
echo