make d
make d_slow
make gen

for ((i = 1; ; i++)) ; do 
    ./gen > test || break
    ./d < test > fast || break
    ./d_slow < test > slow || break
    diff fast slow || break
    echo -n '.'
done
echo
