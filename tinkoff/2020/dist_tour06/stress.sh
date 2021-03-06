make c
make c1
make gen

for ((i = 1; ; i++)) ; do
    ./gen > test || break
    ./c < test > fast || break
    ./c1 < test > ok || break
    diff fast ok || break
    echo -n '.'
done
echo
