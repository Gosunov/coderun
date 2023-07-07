#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int> > a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        if (a[i].first < a[i].second)
            swap(a[i].first, a[i].second);
    }
    vector<pair<int, int> > b = a;
    sort(all(b));
    for (int i = n - 2; i >= 0; --i) {
        b[i].second = max(b[i].second, b[i + 1].second);
    }
    int ans = 0;
    for (auto [x, y] : a) {
        auto it = lower_bound(all(b), make_pair(x + 1, -1));
        if (it == b.end()) {
            ans += 1;
            // cout << '1' << ' ' << x << ' ' << y << '\n';
            continue;
        }
        //cout << x << ' ' << y << ' ';
        // cout << "< " << it->first << ' ' << it->second << '\n';
        if ((*it).second <= y) {
            ans += 1;
            // cout << '3' << ' ' << x << ' ' << y << '\n';
        }
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}