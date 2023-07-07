#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()

const int maxn = 1000500;

int a[maxn];
vector<int> g[maxn];
int used[maxn];
int in[maxn];
set<int> bad;

bool dfs(int v) {
    if (bad.count(a[v]))
        return false;
    for (int u : g[v]) {
        if (!dfs(u))
            return false;
    }
    return true;
} 

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        p--;
        if (p == -1)
            continue;
        g[p].push_back(i);
        in[i]++;
    }
    int k;
    cin >> k;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        bad.insert(x);
    }
    vector<int> ans;
    for (int v = 0; v < n; ++v) {
        if (in[v] == 0 && dfs(v))
            ans.push_back(v);
    }
    cout << ans.size() << '\n';
    for (int i : ans) 
        cout << i + 1 << ' ';
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}