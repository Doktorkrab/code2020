make gen
make h
make h1
for ((i = 0; ; i++)); do
  ./gen >h.in || break
  ./h <h.in >fast || break
  ./h1 <h.in >slow || break
  diff fast slow || break
  echo -n '.'
done
echo
