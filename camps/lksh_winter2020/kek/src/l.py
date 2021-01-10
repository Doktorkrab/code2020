n = int(input())
arr = list(map(int, input().split()))
ans = 0
for i in range(n):
    ans += arr[i] % 2
print(ans)
