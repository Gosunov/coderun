import datetime
import sys

for line in sys.stdin.readlines():
    d, m, y = line.split()
    d = int(d)
    y = int(y)
    match m:
        case "January":
            m = 1
        case "February":
            m = 2
        case "March":
            m = 3
        case "April":
            m = 4
        case "May":
            m = 5
        case "June":
            m = 6
        case "July":
            m = 7
        case "August":
            m = 8
        case "September":
            m = 9
        case "October":
            m = 10
        case "November":
            m = 11
        case "December":
            m = 12

    dt = datetime.datetime(y, m, d)
    # print(dt)
    print(dt.strftime('%A'))