#!/usr/bin/zsh
make d
make d_bamboo
make gen

for (( i = 0; ; i++ )); do
    ./gen > d.in || break
    ./d > fast || break
    ./d_bamboo > slow || break
    diff fast slow  || break
    echo -n '.'
done
echo
echo "Test: "
cat d.in
echo "Fast: "
cat fast
echo "Slow: "
cat slow