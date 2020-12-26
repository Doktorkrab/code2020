make k
make k_slow
make gen

for (( i = 0; ; i++ )); do
      ./gen > test || break
      ./k < test > fast || break
      ./k_slow < test > slow || break
      diff slow fast || break
      echo -n '.'
done
echo