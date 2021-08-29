make gen
make d
make d1

for (( i = 0; ; i++ )); do
    ./gen > d.in || break
    ./d > fast || break
    ./d1 > slow || break
    diff fast slow || break
    echo -n "."
done
echo