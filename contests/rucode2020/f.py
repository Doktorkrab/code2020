import sys
def main():
	s = input()
	n = len(s)
	a = []
	for i in range(n - 1):
		if s[i:i+2] != '10':
			continue
		pr = s[:i]
		sf = s[i+2:]
		# print(pr, sf)
		if not len(sf):
			continue
		if pr == '1' or sf == '1':
			continue
		if pr.endswith('0') or sf.startswith('0'):
			continue
		if not len(pr):
			a.append('10^{'+sf+'}')
			continue
		pr1 = ''
		l = 0
		# print(len(pr))
		if len(pr) == 1:
			pr1 = pr
			l = 1
		else:
			pr1 = pr[0] + '.' + pr[1:]
			l = len(pr[1:])
		if l > int(sf):
			continue
		a.append(pr1 + ' \\cdot 10^{'+sf+'}')
	if not len(a):
		print("Unique")
	else:
		for i in a:
			sys.stdout.write(i + '\n')
main()
