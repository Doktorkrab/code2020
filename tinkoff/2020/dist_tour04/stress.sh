make c
make c_slow
make gen

for ((i = 1; ; i++)) ; do
    ./gen > test || break
    ./c < test > fast || break
    ./c_slow < test > ok || break
    diff fast ok || break
    echo -n '.'
done
echo
