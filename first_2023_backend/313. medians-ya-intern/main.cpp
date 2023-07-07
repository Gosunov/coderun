#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()
#define int long long 

const int maxn = 100500;

int n;

int a[maxn];
int s[maxn];
int t[maxn];

void upd(int i, int x) {
    for (; i < maxn; i |= i + 1)
        t[i] += x;
}

int get(int i) {
    int ans = 0;
    for (; i >= 0; i &= i + 1, --i)
        ans += t[i];
    return ans;
}

int get(int l, int r) {
    return get(r) - get(l - 1); 
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        s[i] = a[i];
    }
    sort(s, s + n);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int idx = lower_bound(s, s + n, a[i]) - s;
        // cout << idx << ' ';
        upd(idx, 1);
        int l = -1;
        int r = n;
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (get(0, m) >= (i + 2) / 2) {
                r = m;
            } else {
                l = m;
            }
        } 
        // cout << r << '\n';
        ans += s[r];
        // cout << r << '\n';
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}