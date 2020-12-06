from datetime import date, timedelta
from sys import stdout


def get(s):
    return date(year=int(s[0:4]), month=int(s[4:6]), day=int(s[6:]))


k, n = map(int, input().split())
days = [0] * 150000
days1 = [0] * 150000
delta = timedelta(days=1)
date_start = date(year=1700, month=1, day=1)


def main():
    for i in range(k):
        date1, date2 = map(get, input().split())
        while date1 != date2:
            days1[(date1 - date_start).days] = 1
            date1 += delta
        days1[(date2 - date_start).days] = 1

    for i in range(n):
        date1, date2 = map(get, input().split())
        while date1 != date2:
            days[(date1 - date_start).days] = 1
            date1 += delta
        days[(date2 - date_start).days] = 1
    start = -1
    l = 0
    was = False

    for i in range(len(days)):
        if days[i] == 1 and days1[i] != 1:
            if start == -1:
                start = i
            l += 1
        else:
            if l > 1:
                date1 = date_start + timedelta(days=start)
                date2 = date_start + timedelta(days=i - 1)
                s = str(date1.day) + '/' + str(date1.month) + '/' + str(date1.year) + ' to '
                s1 = str(date2.day) + '/' + str(date2.month) + '/' + str(date2.year) + '\n'
                was = True
                stdout.write(s)
                stdout.write(s1)
            elif l == 1:
                date1 = date_start + timedelta(days=start)
                s = str(date1.day) + '/' + str(date1.month) + '/' + str(date1.year) + '\n'
                stdout.write(s)
                was = True
            l = 0
            start = -1
    if not was:
        stdout.write("No new information\n")


main()
