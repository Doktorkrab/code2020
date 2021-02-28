make gen
make d
make d1

for (( i = 0; ; i++ )); do
    ./gen > d.in || break
    ./d  > ans || break
    ./d1 > ok || break
    diff ans ok || break
    echo -n '.'
done
echo