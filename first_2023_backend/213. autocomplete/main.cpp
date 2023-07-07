#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()

struct Node {
    int sz = 0;
    Node* next[26];
};

Node* root = new Node();

void insert(string s) {
    Node* cur = root;
    int n = s.size();
    for (int i = 0; i < n; ++i) {
        int c = s[i] - 'a';
        if (!cur->next[c])
            cur->next[c] = new Node();
        cur = cur->next[c];
        cur->sz++;
    }
}

int get(string s) {
    Node* cur = root;
    int n = s.size();
    int i = 0;
    while (i < n && cur->sz != 1) {
        int c = s[i++] - 'a';
        if (!cur->next[c])
            return n;
        cur = cur->next[c]; 
    }
    for (int j = i; j < n; ++j) {
        int c = s[j] - 'a';
        if (!cur->next[c])
            return n;
        cur = cur->next[c]; 
    }
    for (int c = 0; c < 26; ++c) {
        if (cur->next[c])
            return n;
    }
    return min(n, i);
}

void solve() {
    int n;
    cin >> n;
    string word;
    cin >> word;
    insert(word);
    int ans = word.size();

    unordered_set<string> words;
    words.reserve(n);
    words.insert(word);

    for (int i = 1; i < n; ++i) {
        cin >> word;
        int cost = get(word);
        ans += cost;
        if (words.count(word) == 0) {
            insert(word);
            words.insert(word);
        }
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}