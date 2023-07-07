import json
 
def main():
    n, m = map(int, input().split())
    all_rows = {'offers': []}
    for i in range(n):
        feed = json.loads(input())
        all_rows['offers'] += feed['offers']
    all_rows['offers'] = all_rows['offers'][:m]
    print(json.dumps(all_rows, indent=4))
 
 
if __name__ == '__main__':
    main()