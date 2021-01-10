make a
make gen
make a_slow
for (( i = 0; ; i++ )); do
  ./gen > a.in
  /usr/bin/time ./a < a.in > ans || break
#  ./a_slow < a.in > ok || break
#  diff ans ok || break
#  echo -n '.'
done
echo