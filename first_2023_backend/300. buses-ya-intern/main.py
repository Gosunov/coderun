from math import gcd

def f1(a):
    return a, 2

def f2(a, b):
    return 3*a*b - a*a, 6*b

def f3(a, b, c):
    x = a*a*a + 6*a*b*c - 2*a*a*b - 2*a*a*c
    y = 12*b*c
    return x, y

def f4(a, b, c, d):
    x = -3*a*a*a*a + 30*a*b*c*d + 5*a*a*a*(b + c + d) - 10*a*a*(c*d + b*c + b*d)
    y = 60*b*c*d
    return x, y

def f5(a, b, c, d, e):
    x = 2*a*a*a*a*a + 30*a*b*c*d*e - 3*a*a*a*a*(b + c + d + e) - 10*a*a*(b*d*e + c*d*e + b*c*(d + e)) + 5*a*a*a*(d*e + c*d + c*e + b*c + b*d + b*e)
    y = 60*b*c*d*e
    return x, y

n = int(input())
a = list(map(int, input().split()))
a.sort()

x, y = 0, 0
match n:
    case 1: 
        x, y = f1(*a)
    case 2: 
        x, y = f2(*a)
    case 3: 
        x, y = f3(*a)
    case 4: 
        x, y = f4(*a)
    case 5:
        x, y = f5(*a)

g = gcd(x, y)
x, y = x // g, y // g

print('%d/%d' % (x, y))
