#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()

typedef vector<string> Path;

Path to_path(const string& s) {
    Path res;
    stringstream ss(s);
    string dir;
    getline(ss, dir, '/');
    while (getline(ss, dir, '/')) {
        res.push_back(dir);
    }
    return res;
}

struct TreeNode {
    unordered_map<string, TreeNode*> next;
    unordered_map<string, int> deleted;

    string dir = "";

    bool calculated = false;
    bool terminal = false;
};

TreeNode* root = new TreeNode();

string get_ext(const string& dir) {
    auto it = dir.find('.');
    assert(it != string::npos);
    return dir.substr(it);
}

void insert(const Path& path) {
    TreeNode* cur = root;
    for (string dir : path) {
        if (!(cur->next).count(dir))
            (cur->next)[dir] = new TreeNode();
        cur = (cur->next)[dir];
        cur->dir = dir;
    }
    cur->terminal = true;
}

TreeNode* get(const Path& path) {
    TreeNode* cur = root;
    for (string dir : path) {
        if (!(cur->next).count(dir))
            return new TreeNode();
        cur = (cur->next)[dir];
    }
    return cur;
}

void calculate(TreeNode* v, bool deleted) {
    if (v->calculated) {
        return;
    }
    v->calculated = true;
    if (v->terminal) {
        if (deleted) {
            string ext = get_ext(v->dir);
            v->deleted[ext] = 1;
        }
        return;
    }
    for (auto [_, u] : (v->next)) {
        calculate(u, deleted);
        for (auto [ext, k] : u->deleted) {
            v->deleted[ext] += k;
        }
    }
}

void calculate(const Path& path) {
    TreeNode* cur = get(path);
    calculate(cur, true);
}

void solve() {
    int m;
    cin >> m;
    vector<Path> blacklist;
    for (int i = 0; i < m; ++i) {
        string s;
        cin >> s;
        blacklist.push_back(to_path(s));
    }
    sort(all(blacklist), [](const Path& a, const Path& b) {
        return a.size() < b.size();
    });

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        Path path = to_path(s);
        insert(path);
    }

    for (Path blacklisted : blacklist) {
        calculate(blacklisted);
    }
    calculate(root, false);

    int q;
    cin >> q;
    while (q--) {
        string s;
        cin >> s;
        Path path = to_path(s);
        TreeNode* node = get(path);
        cout << (node->deleted).size() << '\n';
        for (auto [ext, k] : node->deleted) {
            cout << ext << ": " << k << '\n';
        }
    }
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}