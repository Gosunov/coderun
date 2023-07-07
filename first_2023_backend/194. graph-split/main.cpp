#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()

const int maxn = 100500;

int n, m;
vector<pair<int, int> > g[maxn];

bool dfs(int v, int x, int c, vector<int>& used, vector<int>& color) {
    if (used[v]) {
        return color[v] == c;
    }
    used[v] = 1;
    color[v] = c;
    for (auto [u, w] : g[v]) {
        if (w < x && !dfs(u, x, c^1, used, color))
            return false;
    }
    return true;
}

bool check(int x) {
    vector<int> used(n);
    vector<int> color(n);
    for (int v = 0; v < n; ++v) {
        if (!used[v]) {
            if (!dfs(v, x, 0, used, color))
                return false;
        }
    }
    return true;
}

void solve() {
    cin >> n >> m;
    int mxw = 1;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
        mxw = max(mxw, w);
    }

    int l = 0;
    int r = mxw + 1;
    while (r - l > 1) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << l << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}