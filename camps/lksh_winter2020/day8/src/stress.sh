make a
make gen
make a_slow
for (( i = 0; ; i++ )); do
  ./gen > a.in
  ./a > ans || break
  ./a_slow > ok || break
  diff -ZiEb ans ok || break
  echo -n '.'
done
echo