make a
make gen
make a_igor
for (( i = 0; ; i++ )); do
  ./gen > test
  ./a < test > ans || break
  ./a_igor < test > ok || break
  diff -ZiEb ans ok || break
  echo -n '.'
done
echo