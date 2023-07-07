#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()
#define int long long

int n, m, q;

vector<set<int> > disabled;
vector<int> a;
vector<int> r;

set<pair<int, int> > mins;
set<pair<int, int> > maxs;

void build() {
    disabled.resize(n);
    a.resize(n);
    r.resize(n, 0);
    for (int i = 0; i < n; ++i) {
        a[i] = m;
    }
    for (int i = 0; i < n; ++i) {
        mins.insert({0, i});
        maxs.insert({0, i});
    }
}

void reset(int i) {
    int prev = r[i] * a[i];
    mins.erase({+prev, i});
    maxs.erase({-prev, i});
    r[i]++;
    disabled[i].clear();
    a[i] = m;
    int score = r[i] * a[i];
    mins.insert({+score, i});
    maxs.insert({-score, i});
}

void disabale(int i, int j) {
    int prev = r[i] * a[i];
    mins.erase({+prev, i});
    maxs.erase({-prev, i});
    disabled[i].insert(j);
    a[i] = m - disabled[i].size();
    int score = r[i] * a[i];
    mins.insert({+score, i});
    maxs.insert({-score, i});
}

int get_max() {
    return (*maxs.begin()).second;
}

int get_min() {
    return (*mins.begin()).second;
}

void solve() {
    cin >> n >> m >> q;
    build();
    while (q--) {
        string cmd;
        cin >> cmd;
        if (cmd == "RESET") {
            int i;
            cin >> i;
            i--;
            reset(i);
        }
        if (cmd == "DISABLE") {
            int i, j;
            cin >> i >> j;
            i--, j--;
            disabale(i, j);
        }
        if (cmd == "GETMAX") {
            cout << get_max() + 1 << '\n';
        }
        if (cmd == "GETMIN") {
            cout << get_min() + 1 << '\n';
        }
        
    }
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}