n, d = input().split()
n = int(n)

offset = 0
match d:
    case 'Monday':
        offset = 0
    case 'Tuesday':
        offset = 1
    case 'Wednesday':
        offset = 2
    case 'Thursday':
        offset = 3
    case 'Friday':
        offset = 4
    case 'Saturday':
        offset = 5
    case 'Sunday':
        offset = 6

for i in range(1, n + offset + 1):
    if i - offset <= 0:
        print('..', end=' ')
        continue
    print('.' + str(i - offset) if i - offset < 10 else i - offset, end=' ')
    if i % 7 == 0:
        print()
