make slow
make main
make gen

for (( i = 0; ; i++ )); do
    ./gen > test || break
    ./slow < test > ok || break
    ./main < test > fast || break
    diff ok fast || break
    echo -n '.'
done
echo