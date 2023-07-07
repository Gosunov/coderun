#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()

int cnt[26];
int need[26];

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = s[i] - 'a';
    }
    cin >> s;
    for (int i = 0; i < s.size(); ++i) {
        need[s[i] - 'a'] = 1;
    }
    int ans = 1e9;
    for (int l = 0; l < n; ++l) {
        vector<int> cur(26);
        for (int r = l; r < n; ++r) {
            cur[a[r]] += 1;
            bool ok = true;
            for (int c = 0; c < 26; ++c) {
                if (need[c] && cur[c] == 0)
                    ok = false;
                if (!need[c] && cur[c] > 0)
                    ok = false;
            }
            if (ok)
                ans = min(ans, r - l + 1);
        }
    }
    cout << (ans == 1e9 ? 0 : ans) << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}