t = int(input())

for i in range(t):

	nums = []
	n, k = map(int, input().split())
	k += 1
	for nines in range(0, 150):
		for start in range(10):
			withPrefix = min(k, 10 - start)
			plusOne = k - withPrefix
			s = 0
			for x in range(k):
				s += (x + start) % 10
			have = n - 9 * nines * withPrefix - plusOne - s

			if have >= 0 and have % (withPrefix + plusOne) == 0:
				have //= withPrefix + plusOne
				# print(have, nines, start)
				ans = ''
				if have % 9 == 0 and have > 0:
					ans += '8'
					have -= 8
				if have % 9 > 0:
					ans += str(have % 9)
				ans += '9' * (have // 9)
				ans += nines * '9'
				ans += str(start)
				nums.append(int(ans))
	if len(nums):
		print(min(nums))
	else:
		print("-1")
