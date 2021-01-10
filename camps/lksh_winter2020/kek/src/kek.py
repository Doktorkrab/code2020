import re

s = r'^CHANGE (\d+?) TO (\d+)'
with open('ans') as f:
    line = f.readline().strip().rstrip()
    if re.fullmatch(s, line) is None:
        exit(1)
    with open('code_inception.cpp') as c_f:
        code = c_f.read()
    a = re.fullmatch(s, line)
    code = code.replace(a.groups()[0], a.groups()[1])
    with open('code_inception.cpp', 'w') as c_f:
        print(code, file=c_f)
        print(a.groups()[0], a.groups()[1])
