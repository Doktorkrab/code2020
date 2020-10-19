make i
make i_slow
make gen

for ((i = 1; ; i++)) ; do 
    ./gen > test || break
    ./i < test > fast || break
    ./i_slow < test > slow || break
    diff fast slow || break
    echo -n '.'
done
echo
