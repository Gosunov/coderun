#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        assert(a[i] <= 1e9);
    }
    sort(all(a));
    int ans = 2e9;
    for (int i = 1; i < n; ++i) {
        ans = min(ans, a[i] ^ a[i - 1]);
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t;
    cin >> t;
    while (t--)
        solve();
}