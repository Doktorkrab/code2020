make gen
make h
make h1

for (( i = 0; ; i++ )); do
    ./gen > test || break
    ./h < test > my || break
    ./h1 < test > ok || break
    diff my ok || break
    echo -n '.'
done