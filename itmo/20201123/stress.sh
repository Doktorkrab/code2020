make d_cube
make d
make gen

for ((i = 1; ; i++)) ; do 
    ./gen > test || break
    ./d < test > fast || break
    ./d_cube < test > slow || break
    diff fast slow || break
    echo -n '.'
done
echo
