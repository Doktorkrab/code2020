make gen
make d
make d1

for (( i = 0; ; i++ )); do
	./gen > test || break
	./d < test > fast || break
	./d1 < test > slow || break
	diff fast slow || break
	echo -n '.'
done