#CXXFLAGS="-g -Wall -Wextra -D_GLIBCXX_DEBUG  -D_GLIBCXX_DEBUG_PEDANTIC -Wconversion -lm -fsanitize=address -fsanitize=bounds -Wshadow -D_FORTIFY_SOURCE=2 -fsanitize=undefined -fno-sanitize-recover -Wformat=2 -std=c++17 -fno-stack-limit -DLOCAL"
make h
make h1
make gen

for ((i = 0; ; i++)) ; do
    ./gen > test || break
    ./h < test > fast || break
    ./h1 < test > slow || break
    diff fast slow || break
    echo -n '.'
done
echo
