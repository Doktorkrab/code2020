make gen
make pieeaters
make pieeaters.stupid

for (( i = 0; ; i++ )); do
	./gen > test || break
	./pieeaters < test > fast || break
	./pieeaters.stupid < test > slow || break
	diff fast slow || break
	echo -n '.'
done