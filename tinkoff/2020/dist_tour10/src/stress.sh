make gen
make b
make b1

for (( i = 0; ; i++ )); do
    ./gen > b.in || break
    ./b  > ans || break
    ./b1 > ok || break
    diff ans ok || break
    echo -n '.'
done
echo