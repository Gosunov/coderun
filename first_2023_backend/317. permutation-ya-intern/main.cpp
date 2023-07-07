#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()
#define int long long 

int isqrt(int x) {
    if (x <= 0)
        return 0;
    int l = -1;
    int r = x;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (m * m >= x)
            r = m;
        else
            l = m;
    }
    return r;
}

void solve() {
    int n;
    cin >> n;
    int a, b, c;
    cin >> a >> b >> c;
    int n1 = n * (n + 1) / 2 - a;
    int n2 = n * (n + 1) * (2 * n + 1) / 6 - b;
    int n3 = n*n * (n + 1)*(n + 1) / 4 - c;
    
    for (int x = 1; x <= n; ++x) {
        int y = +isqrt((2*n2 - n1*n1 + 2*x*n1 - 3*x*x)) / 2 + n1 / 2 - x / 2;
        int z = -isqrt((2*n2 - n1*n1 + 2*x*n1 - 3*x*x)) / 2 + n1 / 2 - x / 2;

        int s1 = x + y + z;
        int s2 = x*x + y*y + z*z;
        int s3 = x*x*x + y*y*y + z*z*z;

        if (n1 == s1 && n2 == s2 && n3 == s3) {
            cout << x << ' ' << y << ' ' << z << '\n';
            return;
        }
    }
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}