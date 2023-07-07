#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()

const int maxn = 100500;

int arr[maxn];

struct Node {
    int mn = +1e9;
    int mx = -1e9;
};

Node merge(const Node& a, const Node& b) {
    return Node{min(a.mn, b.mn), max(a.mx, b.mx)};
}

struct Push {
    bool done = true;
    int val   = 0;
};

Node t[4 * maxn];
Push p[4 * maxn];

void build(int id, int l, int r) {
    if (r - l == 1) {
        t[id] = Node{arr[l], arr[l]};
        return;
    }
    int m = (l + r) / 2;
    build(id * 2 + 1, l, m);
    build(id * 2 + 2, m, r);
    t[id] = merge(t[id * 2 + 1], t[id * 2 + 2]);
}

void push(int id, int l, int r) {
    if (p[id].done)
        return;
    t[id].mx = p[id].val;
    t[id].mn = p[id].val;

    if (r - l > 1) {
        p[id * 2 + 1].done = false;
        p[id * 2 + 2].done = false;
        p[id * 2 + 1].val = p[id].val;
        p[id * 2 + 2].val = p[id].val;
    }
    p[id].done = true;
}

Node get(int id, int l, int r, int lq, int rq) {
    push(id, l, r);
    if (lq <= l && r <= rq)
        return t[id];
    if (r <= lq || rq <= l)
        return Node{};
    int m = (l + r) / 2;
    Node a = get(id * 2 + 1, l, m, lq, rq);
    Node b = get(id * 2 + 2, m, r, lq, rq);
    return merge(a, b);
}

void upd(int id, int l, int r, int lq, int rq, int val) {
    push(id, l, r);
    if (lq <= l && r <= rq) {
        p[id].done = false;
        p[id].val = val;
        push(id, l, r);
        return;
    }
    if (r <= lq || rq <= l) {
        return;
    }
    int m = (l + r) / 2;
    upd(id * 2 + 1, l, m, lq, rq, val);
    upd(id * 2 + 2, m, r, lq, rq, val);
    t[id] = merge(t[id * 2 + 1], t[id * 2 + 2]);
}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    build(0, 0, n);
    while (q--) {
        int a, b, l, r;
        cin >> a >> b >> l >> r;
        l--;
        Node res = get(0, 0, n, l, r);
        // cout << res.mn << ' ' << res.mx << '\n';
        if (res.mn != a || res.mx != a) {
            cout << 0 << '\n';
            continue;
        }
        upd(0, 0, n, l, r, b);
        cout << 1 << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}

