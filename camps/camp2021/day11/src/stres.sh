make gen
make c
make c1

for (( i = 0; ; i++ )); do
    ./gen > c.in || break
    ./c > fast || break
    ./c1 > slow || break
    diff fast slow || break
    echo -n '.'
done
echo