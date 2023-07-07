#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()
#define int long long 

const int maxn = 5050;

int a[maxn];

int n, m, k;

vector<int> ones;

bool found = false;
vector<int> cur;
vector<int> ans;

void f(int t, int l) {
    if (found) {
        return;
    }
    if (t == 1 && (int)cur.size() >= (int)k - (int)ones.size()) {
        found = true;
        ans = cur;
        return;
    }
    if (cur.size() == k) {
        return;
    }
    for (int i = l; i < n; ++i) {
        if (a[i] > 1 && t % a[i] == 0) {
            cur.push_back(i);
            f(t / a[i], i + 1);
            cur.pop_back();
        }
    }
}

void solve() {
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] == 1)
            ones.push_back(i);
    }
    if (m == 0) {
        int l = 0;
        int r = k;
        while (count(a + l, a + r, 0) == 0) {
            l++, r++;
        }
        for (int i = l; i < r; ++i) {
            cout << i + 1 << ' ';
        }
        cout << '\n';
        return;
    }
    f(m, 0);
    for (int i : ans) {
        cout << i + 1 << ' ';
    }
    for (int i = ans.size(); i < k; ++i) {
        static int j = 0;
        cout << ones[j++] + 1 << ' ';
    }
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}