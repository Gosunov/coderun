#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()

char nxt(char c) {
    if (c == 'z')
        return 'a';
    return c + 1;
}

void solve() {
    string s;
    getline(cin, s);
    istringstream str(s);
    vector<string> words;
    string tmp;
    while (str >> tmp) {
        words.push_back(tmp);
    }
    unordered_set st(all(words));

    int q;
    cin >> q;
    while (q--) {
        string word;
        cin >> word;
        for (int shift = 0; shift < 26; ++shift) {
            if (st.count(word)) {
                cout << word << '\n';
                break;
            }
            for (int i = 0; i < word.size(); ++i) {
                word[i] = nxt(word[i]);
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}