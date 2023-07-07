#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()

string from_num(int x) {
    string res = "aaa";
    for (int i = 0; i < 3; ++i) {
        res[2 - i] = 'a' + x % 26;
        x /= 26;
    }
    return res;
}

int from_str(const string& s) {
    return (s[0] - 'a') * 26 * 26 + (s[1] - 'a') * 26 + (s[2] - 'a'); 
}

void solve() {
    vector<vector<int> > g(26 * 26 * 26);
    set<int> vertexes;
    int t;
    cin >> t;
    for (int j = 0; j < t; ++j) {
        string s;
        cin >> s;
        for (int i = 0; i + 3 < s.size(); ++i) {
            int u = from_str(s.substr(i, 3));
            int v = from_str(s.substr(i + 1, 3));
            g[u].push_back(v);
            vertexes.insert(u);
            vertexes.insert(v);
        }
    }
    vector<int> vs;
    vector<int> us;
    vector<int> ws;
    for (int v = 0; v < 26 * 26 * 26; ++v) {
        sort(all(g[v]));
        int m = g[v].size();
        for (int l = 0; l < m;) {
            int r = l;
            int u = g[v][l];
            while (r < m && g[v][r] == u) {
                r++;
            }
            vs.push_back(v);
            us.push_back(u);
            ws.push_back(r - l);
            l = r;
        }
    }

    int n = vertexes.size();
    int m = vs.size();
    cout << n << '\n';
    cout << m << '\n';
    for (int i = 0; i < m; ++i) {
        cout << from_num(vs[i]) << ' ' << from_num(us[i]) << ' ' << ws[i] << '\n'; 
    }
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}