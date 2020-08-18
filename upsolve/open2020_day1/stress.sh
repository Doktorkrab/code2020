make a_100
make a_57
make gen
for (( i = 0; ; i++ )); do
	./gen > test || break
	./a_100 < test > fast || break
	./a_57 < test > slow || break
	diff fast slow || break
	echo -n '.'
done
echo