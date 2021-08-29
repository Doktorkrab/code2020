make d
make d1
make gen
make check

for (( i = 0; ; i++ )); do
    ./gen > d.in || break
    ./d > fast || break
    ./d1 > slow || break
    head -n 1 -q fast slow | ./check || break
    echo -n '.'
done
echo
echo "Test:"
cat d.in
echo "Fast:"
cat fast
echo "Slow:"
cat slow