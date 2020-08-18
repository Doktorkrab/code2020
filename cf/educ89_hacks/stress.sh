make gen
make zayac_d

for (( i = 0; ; i++ )); do
	./gen > test || break
	(time ./zayac_d < test > z) || break
	# sleep 1
done