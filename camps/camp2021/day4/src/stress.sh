#!/usr/bin/zsh
make c
make c1
make gen

for (( i = 0; ; i++ )); do
    ./gen > c.in || break
    ./c > fast || break
    ./c1 > slow || break
    diff fast slow  || break
    echo -n '.'
done
echo
echo "Test: "
cat c.in
echo "Fast: "
cat fast
echo "Slow: "
cat slow