#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()

struct Item {
    int cnt, order, elem;
    bool operator<(const Item& other) const {
        if (cnt != other.cnt)
            return cnt > other.cnt;
        if (order != other.order)
            return order < other.order;
        return elem < other.elem;
    }
    Item(int c, int o, int e) {
        cnt = c;
        order = o;
        elem = e;
    }
};

vector<int> solve2(vector<int> a) {
    int n = a.size();
    vector<int> b = a;
    vector<int> ans(n, -1);
    b.erase(unique(all(b)), b.end());
    for (int i = 0; i < n; ++i) {
        a[i] = lower_bound(all(b), a[i]) - b.begin();
    }

    int m = b.size();
    vector<int> cnt(m);
    for (int i = 0; i < n; ++i) {
        cnt[a[i]] += 1;
    }
    int cnt_max = *max_element(all(cnt));
    int y = 0;
    for (int i = 0; i < m; ++i) {
        y += cnt[i] == cnt_max;
    }

    int lo = 1;
    int hi = n + 1;
    while (hi - lo > 1) {
        int mid = (lo + hi) / 2;
        if (mid * (cnt_max - 1) + y <= n) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    int x = lo;
    set<Item> pq;
    int order = 0;
    for (int i = 0; i < m; ++i) {
        pq.insert({cnt[i], order++, i});
    }

    vector<Item> used;
    for (int i = 0; i < n; ++i) {
        if (i != 0 && i % x == 0) {
            for (Item item : used) {
                pq.insert(item);
            }
            used.clear();
        }
        Item p = *pq.begin();
        pq.erase(pq.begin());
        ans[i] = p.elem;
        if (p.cnt != 1) {
            used.emplace_back(p.cnt - 1, order++, p.elem);
        }
    }
    vector<int> real_ans(n);
    for (int i = 0; i < n; ++i) {
        real_ans[i] = b[ans[i]];
    }
    return real_ans;
}

void solve() {
    int n;
    cin >> n;
    map<int, int> category;
    map<int, vector<int> > products;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        category[x] = y;
        products[y].push_back(x);
        a[i] = y;
    }
    sort(all(a));
    vector<int> ans = solve2(a);
    for (int i = 0; i < n; ++i) {
        int x = products[ans[i]].back();
        products[ans[i]].pop_back();
        cout << x << ' ';
    }
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // solve2({1,1,1,1,2,2,2,3,4,5});
    // solve2({1,1,1,2,3,4,2,3,4});
    // solve2({1,1,1,1,2,2,3,3,4,4});
    // solve2({1,1,1,2,2,2,3,3,3,4,5});
    // solve2({1,1,1,1,1,2,2,2,2,3,3,3,3});
    // solve2({1,1,1,1,1,2,2,2,2,3,3,3});
    solve();
}