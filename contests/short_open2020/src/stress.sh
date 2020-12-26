make d
make d_slow
make gen
for (( i = 0; ; i++ )); do
    ./gen > d.in || break
    ./d > fast || break
    ./d_slow > slow || break
    diff fast slow || break
    echo -n '.'
done