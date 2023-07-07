#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()

const int maxn = 5050;

int n, m;

int g[maxn][maxn];
int color[maxn];
int used[maxn];

bool dfs(int v, int c) {
    if (used[v]) {
        return c == color[v];
    }
    used[v] = 1;
    color[v] = c;
    for (int u = 0; u < n; ++u) {
        if (g[v][u] && !dfs(u, c^1))
            return false;
    } 
    return true;
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            g[i][j] = 1;
        }
    }
    for (int i = 0; i < n; ++i) {
        g[i][i] = 0;
    }
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u][v] = 0;
        g[v][u] = 0;
    }
    for (int v = 0; v < n; ++v) {
        static int c = 0;
        if (!used[v] && !dfs(v, c ^= 1)) {
            cout << -1 << '\n';
            return;
        }
    }
    cout << count(color, color + n, 1) << '\n';
    for (int i = 0; i < n; ++i) {
        if (color[i]) 
            cout << i + 1 << ' ';
    }
    cout << '\n';
    for (int i = 0; i < n; ++i) {
        if (!color[i]) 
            cout << i + 1 << ' ';
    }
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}