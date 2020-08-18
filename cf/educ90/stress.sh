make e
make gen
make e_mark

for (( i = 0; ; i++ )); do
	./gen > test || break
	./e < test > my || break
	./e_mark < test > good || break
	diff my good || break
	echo -n '.'
done