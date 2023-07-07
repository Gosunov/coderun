import requests

def ask(*args):
    url = "http://127.0.0.1:7777/"
    resp = requests.request('MEW', url, headers={
        'X-Cat-Variable': ', '.join(args)
    })
    return resp.headers.get('X-Cat-Value', '').split(', ')


a = input()
b = input()
c = input()
d = input()

aa = ''
bb = ''
cc = ''
dd = ''

q1 = ask(a, b)
q2 = ask(b, c)
if q1 == q2:
    q3 = ask(a, c, d)
    if q3[0] == q3[1]:
        aa = q3[0]
        cc = q3[1]
        dd = q3[2]
        if aa == q1[0]:
            bb = q1[1]
        else:
            bb = q1[0]
    if q3[1] == q3[2]:
        aa = q3[1]
        cc = q3[2]
        dd = q3[0]
        if aa == q1[0]:
            bb = q1[1]
        else:
            bb = q1[0]
else:
    if q1[0] == q2[0]:
        aa = q1[1]
        bb = q1[0]
        cc = q2[1]
    elif q1[0] == q2[1]:
        aa = q1[1]
        bb = q1[0]
        cc = q2[0]
    elif q1[1] == q2[0]:
        aa = q1[0]
        bb = q1[1]
        cc = q2[1]
    elif q1[1] == q2[1]:
        aa = q1[0]
        bb = q1[1]
        cc = q2[0]
    else:
        assert False, 'strange'

    q3 = ask(d)
    dd = q3[0]

print(aa, bb, cc, dd, sep='\n')

