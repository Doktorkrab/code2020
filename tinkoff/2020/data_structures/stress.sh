make l
make l_slow
make gen

for ((i = 1; ; i++)) ; do 
    ./gen > test || break
    ./l < test > fast || break
    ./l_slow < test > slow || break
    diff fast slow || break
    echo -n '.'
done
echo
