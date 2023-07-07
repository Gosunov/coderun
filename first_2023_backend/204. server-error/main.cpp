#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()
#define int long long

void solve() {
    int n;
    cin >> n;
    vector<double> a(n);
    double s = 0;
    for (int i = 0; i < n; ++i) {
        double x, y;
        cin >> x >> y;
        a[i] = x * y / 100;
        s += a[i];
    }
    for (int i = 0; i < n; ++i) {
        cout << a[i] / s << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cout.precision(10),cout.setf(ios_base::fixed);
    solve();
}