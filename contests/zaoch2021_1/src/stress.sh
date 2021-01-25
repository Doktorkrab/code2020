make gen
make i
make i1
#make f1
for (( i = 0; ; i++ )); do
    ./gen > i.in || break
#    ./f1 > slow || break
     ./i > fast || break
     ./i1 > slow || break
    diff slow fast || break
#    head -n 1 fast
#    head -n 1 slow
    echo -n '.'
done
echo