n, m = map(int, input().split())
MOD = 998244353

if n < m:
    print(0)
    exit(0)


def c(a, b):
    # print(" ", a, b)
    # print(fact[b], fact[a - b], fact[a], pow((fact[b] * fact[a - b]) % MOD, -1, MOD))
    return fact[a] * pow((fact[b] * fact[a - b]) % MOD, -1, MOD) % MOD


fact = [1] * max(n + 1, m + 1)
for i in range(1, max(n + 1, m + 1)):
    fact[i] = (fact[i - 1] * i) % MOD
ans = 0
for i in range(0, m):
    # print(pow(m - i, n, MOD), c(i, m))
    # print(pow(-1, i), c(i, m) * pow(m - i, n, MOD) % MOD)
    if i % 2:
        ans -= c(m, i) * pow(m - i, n, MOD) % MOD
    else:
        ans += c(m, i) * pow(m - i, n, MOD) % MOD
    ans %= MOD
print(ans)
