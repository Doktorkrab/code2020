make suffAuto
make gen
make b_stress
for (( i = 0; ; i++ )); do
  ./gen > suffAuto.in
  ./suffAuto < suffAuto.in > ans || break
  ./b_stress < suffAuto.in > ok || break
  diff ans ok || break
  echo -n '.'
done
echo