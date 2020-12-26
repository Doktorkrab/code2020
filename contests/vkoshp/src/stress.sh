make d
make d_slow

for (( i = 1; i < 11; i++ )); do
    for (( j = 1; j <= i; j++ )); do
        echo $i $j > d.in
        ./d < test > fast || break
        ./d_slow < test > slow || break
        diff slow fast || exit
        echo "Test $i $j ok"
    done
done