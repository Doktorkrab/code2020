make a
make gen
for (( i = 0; ; i++ )); do
  ./gen > a.in
  ./a > ans || break
  echo -n '.'
done
echo