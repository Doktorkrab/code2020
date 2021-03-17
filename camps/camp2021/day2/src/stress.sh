#!/usr/bin/zsh
make c
make c_slow
make gen
for (( i = 0; ; i++ )); do
    ./gen > c.in || break
    ./c > fast || break
    ./c_slow > slow || break
    diff fast slow || break
    echo -n '.'
done
echo
echo "Test: "
cat c.in
echo "Fast ans:"
cat fast
echo "Slow ans: "
cat slow