#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()

void solve() {
    map<int, int> mp;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        mp[x]++;
    }
    int mxk = 0;
    for (auto [k, v] : mp) {
        if (mp[mxk] <= v) {
            mxk = k;
        }
    }
    cout << mxk << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}