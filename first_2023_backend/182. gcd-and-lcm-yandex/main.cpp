#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()
#define int long long

void solve() {
    int g, l;
    cin >> g >> l;
    if (l % g != 0) {
        cout << 0 << '\n';
        return;
    }
    int n = l / g;
    int ans = 0;
    for (int x = 1; x * x <= n; ++x) {
        if (int y = n / x; x * y == n) {
            if (gcd(x, y) == 1) {
                ans += 1;
                ans += (x != y);
            }
        }
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cout.precision(10),cout.setf(ios_base::fixed);
    solve();
}