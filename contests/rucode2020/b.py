a, b, c, d, t = map(int, input().split())
s = sum([a, b, c, d])
if t == 4:
	print(int(a == b == c == d))
elif t == 3:
	print(int(len(set([a, b, c, d])) <= 2))
elif t == 2:
	if a == b == c == d:
		print(0)
	elif 2 * a < s and 2 * b < s and 2 * c < s and 2 * d < s:
		print(1)
	else:
		print(0)
elif 2 * a < s and 2 * b < s and 2 * c < s and 2 * d < s:
	print(1)
else:
	print(0)