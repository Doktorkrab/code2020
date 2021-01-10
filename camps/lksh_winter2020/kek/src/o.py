n = int(input())
arr = list(map(int, input().split()))
if n == 1:
    print(1)
else:
    d = arr[1] - arr[0]
    for i in range(1, n - 1):
        if arr[i + 1] - arr[i] != d:
            print("-")
            break
    else:
        print(d)
