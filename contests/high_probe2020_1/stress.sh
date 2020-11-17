make a
make a1

for (( i = 1; ; i++ )); do
    echo $i > test || break
    ./a < test > fast || break
    ./a1 <test > slow || break
    diff fast slow || break
    echo "$i ok!"
done