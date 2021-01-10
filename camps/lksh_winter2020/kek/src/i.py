n = int(input())
arr = [0] * n
for i in range(n):
    arr[i] = ["."] * (2 * n)
for i in range(n):
    for j in range(n - i - 1, n + i + 1, 2):
        arr[i][j] = '['
    for j in range(n - i, n + i + 2, 2):
        arr[i][j] = ']'
for i in range(n):
    print(*arr[i], sep='')
