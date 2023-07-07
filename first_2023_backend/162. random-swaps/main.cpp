#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()
#define double long double

double p[10][20][101];

void solve() {
    string s;
    cin >> s;
    reverse(all(s));
    int n = s.size();
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = s[i] - '0';
    }

    int k;
    cin >> k;
    for (int i = 0; i < n; ++i) {
        p[a[i]][i][0] = 1;
    }
    double i_was_chosen = ((double)(n - 1) / (double)(n * (n - 1) / 2));
    for (int l = 0; l < k; ++l) {
        for (int i = 0; i < n; ++i) {
            for (int d = 0; d < 10; ++d) {
                int cnt = 0;
                double sm = 0;
                for (int j = 0; j < n; ++j) {
                    if (j != i) {
                        cnt += 1;
                        sm += p[d][j][l];
                    }
                }
                
                p[d][i][l + 1] = (i_was_chosen) * (sm / cnt) + (1 - i_was_chosen) * p[d][i][l];
            }
        }
    }
    int sd = 0;
    for (int i = 0; i < n; ++i) {
        sd += a[i];
    }
    double ok  = 0;
    double all = 0;
    for (int d = 0; d < 10; ++d) {
        if ((sd % 3 == 0 && d % 2 == 0) || (d == 5))
            ok += p[d][0][k];
        all += p[d][0][k];
    }
    cout << (ok / all) << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cout.precision(10),cout.setf(ios_base::fixed);
    solve();
}