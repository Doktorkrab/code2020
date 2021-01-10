a, b = map(int, input().split())
sa = ""
sb = ""
for i in range(1, a + 1):
    sa = sa + str(i)
for i in range(1, b + 1):
    sb = sb + str(i)
print(sa, "+", sb, "=", int(sa) + int(sb))