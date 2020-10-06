import random
from math import gcd
from sys import exit

def miller_rabin(x):
    if x == 1 or x == 2:
        return True
    m = x - 1
    s = 0
    while m % 2 == 0:
        s += 1
        m //= 2
    # to_test = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]
    to_test = [random.randint(2, x - 1) for _ in range(50)]
    for t in to_test:
        cur = pow(t, m, x)
        if cur == 1 or cur == x - 1:
            continue
        for j in range(s - 1):
            cur = pow(cur, 2, x)
            if cur == 1:
                return False
            if cur == x - 1:
                break
        else:
            return False
    return True


def f(x, mod):
    return (x * x + 2) % mod


random.seed(239)

n = int(input())
if miller_rabin(n):
    print(-1)
    exit(0)
k = round(n ** 0.5)
while True:
    start = random.randint(0, n - 1)
    cnt = 0
    x0, x1 = start, f(start, n)
    g = gcd((x0 - x1) % n, n)
    # print(start)
    while cnt < max(0, k):
        if 1 < g < n:
            print(g, n // g)
            exit(0)
        x0, x1 = f(x0, n), f(f(x1, n), n)
        g = gcd((x0 - x1) % n, n)
        cnt += 1
