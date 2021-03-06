make d
make gen

for (( i = 0; ; i++ )); do
  ./gen > d.in || break
  ./d > /dev/null || break
  echo -n '.'
done