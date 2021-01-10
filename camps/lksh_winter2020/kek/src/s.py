n, m, k = map(int, input().split())
i = 1
j = 1
i += k
j += k
i %= n
j %= m
if i == 0:
    i = n
if j == 0:
    j = m
print(i, j)