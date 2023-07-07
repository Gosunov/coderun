#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()

const int maxn = 300500;

int seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 mt(seed);
 
struct Treap {
    int cnt, x, y;
    Treap *l, *r;
    Treap() {}
    Treap(int x) : x(x), y(mt()), l(0), r(0) {}
};
 
int cnt(Treap *t) {
    return t ? t->cnt : 0;
}
 
void upd(Treap *t) {
    if (t) {
        t->cnt = 1 + cnt(t->l) + cnt(t->r);
    }
}
 
void merge(Treap *l, Treap *r, Treap *&t) {
    if (!l || !r)
        t = l ? l : r;
    else if (l->y > r->y)
        merge(l->r, r, l->r), t = l;
    else
        merge(l, r->l, r->l), t = r;
    upd(t);
}
 
void split(Treap *t, Treap *&l, Treap *&r, int x) {
    if (!t) {
        l = r = 0;
        return;
    }
    if (x < t->x)
        split(t->l, l, t->l, x), r = t;
    else
        split(t->r, t->r, r, x), l = t;
    upd(t);
}

void splitByPos(Treap *t, Treap *&l, Treap *&r, int pos) {
    if (!t) {
        l = r = 0;
        return;
    }
    if (pos <= cnt(t->l))
        splitByPos(t->l, l, t->l, pos), r = t;
    else
        splitByPos(t->r, t->r, r, pos - 1 - cnt(t->l)), l = t;
    upd(t);
}

int answer(Treap *t, int x) {
    if (!t)
        return 0;
    if (x < t->x)
        return answer(t->l, x);
    else
        return cnt(t->l) + 1 + answer(t->r, x);
    upd(t);
}

int n, m;

int a[maxn];
int b[maxn];

void decode() {
    vector<int> id(m);
    unordered_map<int, int> rid;
    rid.reserve(m);
    for (int i = 0; i < m; ++i) {
        id[i] = i;
        rid[i] = i;
    }
    Treap* t = nullptr;
    for (int i = 0; i < m; ++i) {
        merge(t, new Treap(id[i]), t);
    }
    int min_id = 0;
    for (int i = 0; i < n; ++i) {
        Treap* l;
        Treap* mid;
        Treap* r;
        splitByPos(t, l, r, a[i]);
        splitByPos(r, mid, r, 1);
        b[i] = rid[mid->x];
        mid->x = --min_id;
        rid[mid->x] = b[i];
        merge(mid, l, t);
        merge(t, r, t);
    }
}
    
void encode() {
    vector<int> id(m);
    for (int i = 0; i < m; ++i) {
        id[i] = i;
    }
    Treap* t = nullptr;
    for (int i = 0; i < m; ++i) {
        merge(t, new Treap(id[i]), t);
    }
    int min_id = 0;
    for (int i = 0; i < n; ++i) {
        int x = id[a[i]];
        b[i] = answer(t, x) - 1;
        Treap* l;
        Treap* mid;
        Treap* r;
        split(t, l, r, x - 1);
        split(r, mid, r, x);
        mid->x = id[a[i]] = --min_id;
        merge(mid, l, t);
        merge(t, r, t);
    }
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int type;
    cin >> n >> m >> type;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i]--;
    }
    if (type == 1)
        encode();
    if (type == 2)
        decode();
    for (int i = 0; i < n; ++i) {
        cout << b[i] + 1 << ' ';
    }
    cout << '\n';
}