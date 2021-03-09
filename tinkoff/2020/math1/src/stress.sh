make gen
make j
make j1

for (( i = 0; ; i++ )); do
    ./gen > j.in || break
    ./j > ans || break
    ./j1 > right || break
    diff ans right || break
    echo -n '.'
done
echo