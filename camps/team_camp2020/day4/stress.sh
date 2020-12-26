make f
make f_slow
make gen

for (( i = 0; ; i++ )); do
      ./gen > test || break
      ./f < test > fast || break
      ./f_slow < test > slow || break
      diff slow fast || break
      echo -n '.'
done
echo