make c
make c_slow
make gen
for (( i = 0; ; i++ )); do
  ./gen > c.in
  ./c > ans || break
  ./c_slow > ok || break
  diff ok ans || break
  echo -n '.'
done
echo