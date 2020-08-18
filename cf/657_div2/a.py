def kek(s):
	c = 0
	for i in range(len(s) - 6):
		if s[i:i + 7] == 'abacaba':
			c += 1
	return c
t = int(input())
gg = 'abacaba'
for tt in range(t):
	n = int(input())
	s = input()
	if kek(s) > 1:
		print('No')
		continue
	elif kek(s) == 1:
		print('Yes')
		print(s.replace('?', 'z'))
		continue
	for i in range(n - 6):
		good = True
		for j in range(7):
			good = good and (s[i + j] == '?' or s[i + j] == gg[j])
		if good:
			t = (s[:i] + 'abacaba' + s[i + 7:]).replace('?', 'z')
			# print(s, t, kek )
			if kek(t) == 1:
				print('Yes')
				print(t)
				break
	else:
		print('No')