#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()
#define int long long

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<int> b(m);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }
    sort(all(a));
    sort(all(b), greater<int>());
    int ans = 0;
    int buy = 0;
    int sell = 0;
    for (int i = 0; i < n && i < m; ++i) {
        buy += a[i];
        sell += b[i];
        ans = max(ans, sell - buy);
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}