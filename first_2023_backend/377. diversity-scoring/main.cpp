#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()
#define int long long

void solve() {
    int n;
    cin >> n;
    map<int, int> category;
    map<int, vector<int> > mp;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        category[x] = y;
    }
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        int y = category[x];
        mp[y].push_back(i);
    }

    int ans = n;
    for (auto& [k, v] : mp) {
        int m = v.size();
        for (int i = 1; i < m; ++i) {
            ans = min(ans, v[i] - v[i - 1]);
        }
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}