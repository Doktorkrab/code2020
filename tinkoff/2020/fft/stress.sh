make gen
make fft
for (( i = 0; ; i++ )); do
    ./gen > test || break
    python a.py < test > ans || break
    ./fft < test > fast || break
    diff ans fast || break
    echo -n '.'
done
echo