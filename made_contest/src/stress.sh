make gen
make d
make d_slow

for (( i = 0; ; i++ )); do
    ./gen > d.in || break
    ./d > fast || break
    ./d_slow > slow || break
    diff fast slow || break
    echo -n '.'
done
echo