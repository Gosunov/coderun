s = input()
t = input()

ans = 0
for c in t:
    if c in s:
        ans += 1
print(ans)