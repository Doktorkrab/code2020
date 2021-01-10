a, b = input().split()
a: str = a
b: str = b
if not a.isdigit():
    if a.startswith('-'):
        ans = '-oo'
    else:
        ans = 'oo'
    print(f"{a} - {b} = {ans}")
elif not b.isdigit():
    if a.startswith('-'):
        ans = 'oo'
    else:
        ans = '-oo'
    print(f"{a} - {b} = {ans}")
else:
    print(f"{a} - {b} = {int(a) - int(b)}")
