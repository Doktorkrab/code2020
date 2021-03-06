make b
make b_slow
make gen

for ((i = 1; ; i++)) ; do 
    ./gen > test || break
    ./b < test > fast || break
    ./b_slow < test > slow || break
    diff fast slow || break
    echo -n '.'
done
echo
