#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()
#define int long long

int coef_len(int k) {
    assert(k >= 0);
    if (k == 0)
        return 0;
    if (k == 1)
        return 1;
    return to_string(k).size() + 1;
}

vector<int> parse_coefs(const string& s) {
    int n = s.size();
    vector<int> res;
    for (int i = 0; i < n; ++i) {
        int j = i;
        while ('0' <= s[j] && s[j] <= '9') {
            j += 1;
        }
        int k = 1;
        if (j > i) {
            string num = s.substr(i, j - i);
            k = stoll(num);
        }
        i = j;
        res.push_back(k);
    }
    return res;
}

vector<int> build_prefs(const vector<int>& coefs) {
    int n = coefs.size();
    vector<int> pref(n + 1);
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] + coefs[i];
    }
    return pref;
}

vector<int> build_prefs_len(const vector<int>& coefs) {
    int n = coefs.size();
    vector<int> pref(n + 1);
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] + coef_len(coefs[i]);
    }
    return pref;
}

void solve() {
    string s;
    cin >> s;
    vector<int> coefs = parse_coefs(s);
    vector<int> prefs = build_prefs(coefs);
    vector<int> prefs_len = build_prefs_len(coefs);

    /* for (int i : prefs) {
        cout << i << ' ';
    }
    cout << '\n';
    for (int i : prefs_len) {
        cout << i << ' ';
    }
    cout << '\n'; */

    int q;
    cin >> q;
    while (q--) {
        int lq, rq;
        cin >> lq >> rq;
        // cout << lq << ' ' << rq << ": ";
        int i = lower_bound(all(prefs), lq) - prefs.begin();
        int j = lower_bound(all(prefs), rq) - prefs.begin();
        // cout << i << ' ' << j << '\n';
        if (i == j) {
            cout << coef_len(rq - lq + 1) << '\n';
            continue;
        }
        int x = prefs[i] - lq + 1;
        int y = rq - prefs[j - 1];
        int ans = coef_len(x) + coef_len(y);
        ans += prefs_len[j - 1] - prefs_len[i];
        cout << ans << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}