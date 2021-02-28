make gen
make m
make m1
for (( i = 0; ; i++ )); do
    ./gen > m.in || break
    ./m1 > slow || break
    ./m > fast || break
    diff slow fast || break
    echo -n '.'
done
echo