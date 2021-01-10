n = int(input())
arr = list(map(int, input().split()))
cnt = 0
cur = arr[0]
for i in range(n):
    if arr[i] == cur:
        cnt += 1
    else:
        if cnt == 1:
            print(cur, end=' ')
        cnt = 1
        cur = arr[i]
    print(arr[i], end=' ')
if cnt == 1:
    print(cur, end=' ')
