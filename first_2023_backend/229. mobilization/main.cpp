#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()
#define int long long

const int maxn = 200500;

int n;

int a[maxn];
int b[maxn];

set<pair<int, int> > x;
set<pair<int, int> > y;

int sa = 0;
int sb = 0;

void del(int i) {
    if (x.count({b[i] - a[i], i})) {
        sa -= a[i];
        x.erase({b[i] - a[i], i});
    }
    if (y.count({b[i] - a[i], i})) {
        sb -= b[i];
        y.erase({b[i] - a[i], i});
    }
    if (x.size() < y.size()) {
        auto it = y.begin();
        sb -= b[it->second];
        sa += a[it->second];
        x.insert(*it);
        y.erase(it);
    }
}

void insert(int i) {
    // cout << i << '\n';
    x.insert({b[i] - a[i], i});
    sa += a[i];
    if (x.size() > n / 2) {
        auto it = x.rbegin();
        sa -= a[it->second];
        sb += b[it->second];
        y.insert(*it);
        x.erase(x.find(*it));
    }
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    for (int i = 0; i < n; ++i) {
        insert(i);
    }

    int q;
    cin >> q;
    while (q--) {
        int i, t, d;
        cin >> i >> t >> d;
        i--;
        del(i);
        if (t == 1) {
            a[i] += d;
        }
        if (t == 2) {
            b[i] += d;
        }
        insert(i);
        cout << sa + sb << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}