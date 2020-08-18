make gen
make f
make f1

for (( i = 0; ; i++ )); do
	./gen > test || break
	./f < test > fast || break
	./f1 < test > slow || break
	diff fast slow || break
	echo -n '.'
done