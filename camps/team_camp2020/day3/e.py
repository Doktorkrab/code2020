p = int(input())
q = int(input())
if p % q:
    print(p)
else:
    print(p // q * (q - 1))