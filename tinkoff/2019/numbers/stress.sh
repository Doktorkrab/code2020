bld gen
bld i
bld i_slow

for (( i = 0; ; i++ )); do
	./gen > test || break
	./i < test > my_ans || break
	./i_slow < test > right_ans || break
	diff my_ans right_ans || break
	echo -n '.'
done