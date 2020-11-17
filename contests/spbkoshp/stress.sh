make a
make a_slow
make gen

for (( i = 1; ; i++ )); do
#    echo $i > test
    ./gen > test || break
    ./a < test > fast || break
    ./a_slow < test > slow || break
    diff fast slow || break
    echo "$i ok"
done