#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()
#define int long long

const int mod = 1000000007;

int C [11][11];
int pC[11][11];
int dp[51][52][52][251];
int a [51];
int s [51];

int binpow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1) {
        if (y & 1)
            res = res * x % mod;
        x = x * x % mod;
    }
    return res;
}

int inv(int x) {
    return binpow(x, mod - 2);
}

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        s[i + 1] = s[i] + a[i];
    }
    dp[0][0][0][0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int s1 = 0; s1 <= 50; ++s1) {
            for (int s2 = 0; s2 <= 50; ++s2) {
                for (int t = 0; t <= 250; ++t) {
                    for (int k = 0; k <= a[i] && t + k <= 250; ++k) {
                        if (k == 0) {
                            dp[i + 1][s1][s2 + 1][t + k] += dp[i][s1][s2][t] * C[a[i]][k] % mod;
                            if (dp[i + 1][s1][s2 + 1][t + k] > mod) 
                                dp[i + 1][s1][s2 + 1][t + k] -= mod;
                        } else if (k == a[i]) {
                            dp[i + 1][s1 + 1][s2][t + k] += dp[i][s1][s2][t] * C[a[i]][k] % mod;
                            if (dp[i + 1][s1 + 1][s2][t + k] > mod) 
                                dp[i + 1][s1 + 1][s2][t + k] -= mod;
                        } else {
                            dp[i + 1][s1 + 1][s2 + 1][t + k] += dp[i][s1][s2][t] * C[a[i]][k] % mod;
                            if (dp[i + 1][s1 + 1][s2 + 1][t + k] > mod) 
                                dp[i + 1][s1 + 1][s2 + 1][t + k] -= mod;
                        }
                    }
                }
            }
        }
    }
    int ok = 0;
    for (int i = 0; i <= 50; ++i) {
        ok += dp[n][i][i][s[n] / 2];
        ok %= mod;
    }
    int total = 0;
    for (int i = 0; i <= 50; ++i) {
        for (int j = 0; j <= 50; ++j) {
            total += dp[n][i][j][s[n] / 2];
            total %= mod;
        }
    }
    cout << ok * inv(total) % mod << '\n';
}

signed main() {
    for (int i = 0; i <= 10; ++i) {
        C[i][0] = 1;
        C[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
    for (int i = 0; i <= 10; ++i) {
        for (int j = 0; j <= i; ++j) {
            pC[i][j] = C[i][j] * inv(1 << i) % mod;
        }
    }
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}