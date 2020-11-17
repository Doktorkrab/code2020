make e
make e1
make gen

for ((i = 1; ; i++)) ; do 
    ./gen > test || break
    ./e < test > fast || break
#    ./e1 < test > slow || break
#    diff fast slow || break
    echo -n '.'
done
echo
