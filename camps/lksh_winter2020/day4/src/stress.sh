make f
make gen
make f_slow
for (( i = 0; ; i++ )); do
  ./gen > f.in
  ./f < f.in > ans || break
  ./f_slow < f.in > ok || break
  diff ans ok || break
  echo -n '.'
done
echo