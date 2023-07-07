#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()

string tel[1000];
string ans[1000];

string normalize(const string& s) {
    string res = "";
    for (char c : s) {
        if ('0' <= c && c <= '9')
            res += c;
    }
    return res;
}

void solve() {
    string tmp;
    int n;
    cin >> n;
    getline(cin, tmp);
    for (int i = 0; i < n; ++i) {
        getline(cin, tel[i]);
        tel[i] = normalize(tel[i]);
        // cout << tel[i] << '\n';
    }
    int q;
    cin >> q;
    getline(cin, tmp);
    while (q--) {
        string t;
        getline(cin, t);
        for (int p = 0; p < n; ++p) {
            string s = tel[p];
            string res = "";
            int i = 0;
            int j = 0;
            bool ok = true;
            while (i < s.size() && t[j] != '-') {
                if (t[j] == 'X') {
                    res += s[i];
                    i++;
                    j++;
                    continue;
                }
                if ('0' <= t[j] && t[j] <= '9') {
                    if (s[i] != t[j])
                        ok = false;
                    res += s[i];
                    i++;
                    j++;
                    continue;
                }
                res += t[j++];
            }
            int jj = j;
            
            while (t[jj] != '-') {
                if (t[jj] == 'X' || ('0' <= t[jj] && t[jj] <= '9')) {
                    ok = false;
                    break;
                }
                jj++;
            }
            if (!ok) 
                continue;
            if (i == s.size()) {
                while (j < t.size())
                    res += t[j++];
                ans[p] = res;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        assert(!ans[i].empty());
        cout << ans[i] << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}