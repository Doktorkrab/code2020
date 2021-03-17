make a
make a_slow
make gen

for (( i = 0; ; i++ )); do
    ./gen > a.in || break
    ./a > fast || break
    ./a_slow > slow || break
    diff fast slow || break
    echo -n '.'
done
echo
echo "Test"
cat a.in
echo "Fast ans:"
cat fast
echo "Slow ans:"
cat slow