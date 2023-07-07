#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()

void solve() {
    int n;
    cin >> n;
    map<int, int> mp;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        mp[x]++;
    }
    int ans = 0;
    for (auto [k, v] : mp) {
        ans += v == 1;
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}