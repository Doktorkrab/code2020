make gen
make b
make b_slow

for (( i = 0; ; i++ )); do
    ./gen > b.in || break
    ./b > fast || break
    ./b_slow > slow || break
    diff fast slow > /dev/null || break
    echo -n '.'
done
echo
echo "Test:"
cat b.in

echo "Slow:"
cat slow


echo "Fast:"
cat fast