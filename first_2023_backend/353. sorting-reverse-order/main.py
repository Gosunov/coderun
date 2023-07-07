from urllib.request import urlopen
import json
 
server = input()
port = input()
a = input()
b = input()
 
 
url = "%s:%s?a=%s&b=%s" % (server, port, a, b)
data = json.loads(urlopen(url).read())
print("\n".join(map(str, filter(lambda x : x > 0, sorted(data, reverse = True)))))