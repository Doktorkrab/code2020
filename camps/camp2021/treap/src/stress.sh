make gen
make f
make f_slow
for (( i = 0; ; i++ )); do
    ./gen > f.in || break
    ./f > fast || break
    ./f_slow > slow || break
    diff fast slow || break
    echo -n '.'
done
echo