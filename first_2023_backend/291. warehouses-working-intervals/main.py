from datetime import date

a = []
for line in open('input.txt', 'r').readlines():
    line = line.strip()
    uid, timerange, prod = line.split(',')
    uid = int(uid)
    start, finish = timerange.split()
    start  = date.fromisoformat(start)
    finish = date.fromisoformat(finish)
    if prod == "NULL":
        a.append([uid, start, finish, "KGT"])
        a.append([uid, start, finish, "COLD"])
        a.append([uid, start, finish, "OTHER"])
    else:
        a.append([uid, start, finish, prod])

a.sort(key=lambda x: (x[0], len(x[3]), x[1]))
ans = []
for uid, start, finish, prod in a:
    if not ans:
        ans.append([uid, start, finish, prod])
        continue
    if uid == ans[-1][0] and prod == ans[-1][3] and start <= ans[-1][2]:
        ans[-1][2] = max(finish, ans[-1][2])
    else:
        ans.append([uid, start, finish, prod])

for uid, start, finish, prod in ans:
    start  = start.isoformat()
    finish = finish.isoformat()

    print(f'{uid},{start} {finish},{prod}')
