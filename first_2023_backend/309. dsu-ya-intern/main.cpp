#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()

const int maxn = 100500;

int n, m;

int k;

int p[maxn];
int sz[maxn];

void build() {
    iota(p, p + n, 0);
    fill(sz, sz + n, 1);
    k = n;
}

int get(int x) {
    if (x == p[x])
        return x;
    return p[x] = get(p[x]);
}

void connect(int x, int y) {
    x = get(x);
    y = get(y);
    if (x == y)
        return;
    if (sz[x] > sz[y])
        swap(x, y);
    sz[y] += sz[x];
    p[x] = y;
    k -= 1;
}

void solve() {
    cin >> n >> m;
    vector<pair<int, int> > edges;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (u > v)
            swap(u, v);
        edges.emplace_back(u, v);
    }
    build();
    map<pair<int, int>, int> mp;
    for (auto edge : edges) {
        ++mp[edge];
    }
    int q;
    cin >> q;
    vector<int> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i];
        --queries[i];
        --mp[edges[queries[i]]];
    }
    for (auto [edge, v] : mp) {
        if (v == 0)
            continue;
        connect(edge.first, edge.second);
    }
    vector<int> ans(q);
    for (int i = q - 1; i >= 0; --i) {
        ans[i] = k;
        auto edge = edges[queries[i]];
        if ((++mp[edge]) == 1)
            connect(edge.first, edge.second);
    }
    for (int i = 0; i < q; ++i) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    solve();
}