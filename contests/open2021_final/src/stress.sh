make winner
make winner_slow
make gen

for (( i = 0; ; i++ )); do
  ./gen > winner.in || break
  ./winner > ans || break
  ./winner_slow > right || break
  diff ans right || break
  echo -n '.'
done
echo