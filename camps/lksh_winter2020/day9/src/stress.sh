make c
make gen
for (( i = 0; ; i++ )); do
  ./gen > c.in
  ./c > ans || break
  echo -n '.'
done
echo