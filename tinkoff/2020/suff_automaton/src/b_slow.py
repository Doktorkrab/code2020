n = int(input())
arr = [input() for _ in range(n)]
ans = [0] * (n + 1)
for i in range(n):
    for l in range(n):
        for r in range(l + 1, n + 1):
            s = arr[i][l:r]
            cnt = 0
            for x in arr:
                if s in x:
                    cnt += 1
            ans[cnt] = max(ans[cnt], r - l)
print(*ans[2:], sep='\n')