make i
#make b_ok
make gen

for ((i = 1; ; i++)) ; do
    ./gen > test || break
    ./i < test > fast || break
#    ./b_ok < test > ok || break
#    diff fast ok || break
    echo -n '.'
done
echo
