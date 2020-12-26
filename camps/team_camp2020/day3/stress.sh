make h
make h_slow
make gen

for (( i = 0; ; i++ )); do
      ./gen > test || break
      ./h < test > fast || break
      ./h_slow < test > slow || break
      diff slow fast || break
      echo -n '.'
done
echo