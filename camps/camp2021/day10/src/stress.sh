make gen
make b
make b_bins

for (( i = 0; ; i++ )); do
  ./gen > b.in || break
  ./b > slow || break
  ./b_bins > fast || break
  diff slow fast || break
  echo -n '.'
done