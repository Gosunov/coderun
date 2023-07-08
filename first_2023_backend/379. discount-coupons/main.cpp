#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()
#define double long double
#define ld double

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<double> cost(n);
    for (int i = 0; i < n; ++i) {
        cin >> cost[i];
    }
    vector<int> coupons(n);
    for (int i = 0; i < n; ++i) {
        int c;
        cin >> c;
        int st = 0;
        for (int j = 0; j < c; ++j) {
            int x;
            cin >> x;
            --x;
            st |= (1 << x);
        }
        coupons[i] = st;
    }
    vector<int> discount(m);
    for (int i = 0; i < m; ++i) {
        cin >> discount[i];
    }

    int set = (1 << k) - 1;
    int limit = (1 << m);
    double bestScore = 1e9;
    int    bestMask  = 0; 
    while (set < limit) {
        vector<double> tcost = cost;
        for (int i = 0; i < n; ++i) {
            int d = coupons[i] & set;
            for (int j = 0; j < m; ++j) {
                if ((d >> j) & 1)
                    tcost[i] *= (ld)1 - (ld)discount[j] / (ld)100;
            }
        }
        double score = accumulate(all(tcost), (ld)0);
        if (score < bestScore) {
            bestMask = set;
            bestScore = score;
        }
        // Gosper's hack:
        int c = set & - set;
        int r = set + c;
        set = (((r ^ set) >> 2) / c) | r;
    }
    vector<int> ans;
    for (int i = 0; i < m; ++i) {
        if ((bestMask >> i) & 1)
            ans.push_back(i);
    }
    cout << ans.size() << '\n';
    for (int i : ans) {
        cout << i + 1 << ' ';
    }
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}