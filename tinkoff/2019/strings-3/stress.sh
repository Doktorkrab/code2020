make d
make d_stupid
make gen

for (( i = 1; ; i++ )); do
	./gen > test || break
	./d < test > my || break
	./d_stupid < test > ok || break
	diff -iEZbwB my ok || break
	echo -n '.'
done