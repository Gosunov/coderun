k, m, d = map(int, input().split())
d -= 1

a = 1
extra = 0
stopped = False
while d != 0:
    if d != 5 and d != 6:
        m += k
    m -= a
    a += 1
    if m < 0:
        print(extra)
        stopped = True
        break
    extra += 1
    d = (d + 1) % 7

def sum_range(fr, to):
    return (to + 1) * to // 2 - (fr - 1) * fr // 2


def check(x):
    need = sum_range(a, a + x - 1)
    weeks = x // 7
    books = m + weeks * 5 * k
    books += k * min(5, x % 7)
    return books >= need

l = 0
r = 100000000000
if not stopped:
    while r - l > 1:
        mid = (r + l) // 2
        if check(mid):
            l = mid
        else:
            r = mid
    print(l + extra)