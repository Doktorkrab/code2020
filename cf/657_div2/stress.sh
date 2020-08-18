make gen
make c
make c_f

for (( i = 0; ; i++ )); do
	./gen > test || break
	./c < test > fast || break
	./c_f < test > slow || break
	diff fast slow || break
	echo -n '.'
done