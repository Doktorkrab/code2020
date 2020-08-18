make e
make gen


for (( i = 1; ; i++ )); do
	./gen > test || break
	./e < test > ans
	tail -n 1 test | tee > right
	diff right ans || break
	echo -n '.'
done