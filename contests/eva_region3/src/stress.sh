make d
make gen

for (( i = 0; ; i++ )); do
    ./gen > d.in || break
    ./d > ans || break
    echo -n '.'
done