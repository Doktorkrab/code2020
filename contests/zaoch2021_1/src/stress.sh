make gen
make f
#make f1
for (( i = 0; ; i++ )); do
    ./gen > f.in || break
#    ./f1 > slow || break
    /usr/bin/time ./f > fast
#    diff slow fast || break
#    head -n 1 fast
#    head -n 1 slow

done
echo