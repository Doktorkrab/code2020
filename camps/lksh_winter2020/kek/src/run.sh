while true; do
    make code_inception 2> /dev/null > /dev/null|| break
    ./code_inception || break
    python3 kek.py || break
    echo "CHANGED"
done