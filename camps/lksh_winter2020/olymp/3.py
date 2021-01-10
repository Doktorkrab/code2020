n = 2000 + 10
dp1 = [0] * n
for i in range(n):
    dp1[i] = [0] * n
dp1[0][0] = 1
for i in range(1, n):
    for j in range(i):
        dp1[i][j] = dp1[i - 1][j]
        if (j != 0):
            dp1[i][j] += dp1[i][j - 1]
dp2 = [0] * n
for i in range(n):
    dp2[i] = [0] * n

dp2[0] = [1] * n
for i in range(1, n):
    for j in range(i, n):
        dp2[i][j] = dp2[i - 1][j] + dp2[i][j - 1]
t = int(input())
for i in range(t):
    a, b = map(int, input().split('-'))
    print(dp1[a][b], end=' ')
    ans = 0
    for j in range(a + 1):
        ans += dp2[j][b - 1]
    print(ans % (10 ** 9 + 7))