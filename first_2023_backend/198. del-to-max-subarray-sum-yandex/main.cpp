#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()
#define int long long

const int inf = 1e9 + 500;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    if (*max_element(all(a)) <= 0) {
        cout << *max_element(all(a)) << '\n';
        return;
    }

    int ans = -inf;
    vector<vector<int> > dp(n + 1, vector<int>(k + 1, -inf));
    for (int i = 0; i < n; ++i) {
        dp[i + 1][0] = max(dp[i][0] + a[i], a[i]);
        ans = max(ans, dp[i + 1][0]);
    }
    for (int j = 1; j <= k; ++j) {
        for (int i = 0; i < n; ++i) {
            dp[i + 1][j] = max(dp[i][j] + a[i], dp[i][j - 1]);    
            ans = max(ans, dp[i + 1][j]);
        }
    }

    vector<vector<int> > pref(n + 1, vector<int>(k + 1, -inf));
    vector<vector<int> > suff(n + 1, vector<int>(k + 1, -inf));
    pref[0][0] = 0;
    suff[n][0] = 0;

    for (int i = 0; i < n; ++i) {
        pref[i + 1][0] = pref[i][0] + a[i];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= k; ++j) {
            pref[i + 1][j] = max(pref[i][j] + a[i], pref[i][j - 1]);    
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        suff[i][0] = suff[i + 1][0] + a[i];
    }
    for (int i = n - 1; i >= 0; --i) {
        for (int j = 1; j <= k; ++j) {
            suff[i][j] = max(suff[i + 1][j] + a[i], suff[i + 1][j - 1]);    
        }
    }

    vector<vector<int> > best_pref(n + 1, vector<int>(k + 1, -inf));
    vector<vector<int> > best_suff(n + 1, vector<int>(k + 1, -inf));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= k; ++j) {
            best_pref[i + 1][j] = max(best_pref[i + 1][j], best_pref[i][j]);
            best_pref[i + 1][j] = max(best_pref[i + 1][j], pref[i + 1][j]);
            if (j - 1 >= 0)
                best_pref[i + 1][j] = max(best_pref[i + 1][j], best_pref[i + 1][j - 1]);
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j <= k; ++j) {
            best_suff[i][j] = max(best_suff[i][j], best_suff[i + 1][j]);
            best_suff[i][j] = max(best_suff[i][j], suff[i][j]);
            if (j - 1 >= 0)
                best_suff[i][j] = max(best_suff[i][j], best_suff[i][j - 1]);
        }
    }

    for (int i = 1; i < n; ++i) {
        for (int p = 0; p <= k; ++p) {
            ans = max(ans, best_pref[i][p] + best_suff[i][k - p]);
        }
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