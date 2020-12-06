n, k = map(int, input().split())
vars = n // k
vars1 = 0
if k % 2 == 0:
    vars1 = (n + k // 2) // k
print((vars ** 3) + (vars1 ** 3))
