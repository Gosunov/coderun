#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()

const int maxn = 1005;
int a[maxn][maxn];

int n, m;

int color(int i, int j) {
    if (!(0 <= i && i < n && 0 <= j && j < m))
        return 1;
    return a[i][j];
}

void solve() {
    cin >> n >> m;
    int kw;
    cin >> kw;
    while (kw--) {
        int i, j;
        cin >> i >> j;
        i--, j--;
        a[i][j] = 2;
    }
    int kb;
    cin >> kb;
    while (kb--) {
        int i, j;
        cin >> i >> j;
        i--, j--;
        a[i][j] = 3;
    }
    int cur;
    string tmp;
    cin >> tmp;
    if (tmp == "white")
        cur = 2;
    if (tmp == "black")
        cur = 3;

    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            
            if (
                   color(i, j) == cur
                && color(i + 1, j + 1) == (cur^1)
                && color(i + 2, j + 2) == 0
            ) {
                cout << "Yes" << '\n';
                return;
            }
            if (
                   color(i, j) == cur
                && color(i + 1, j - 1) == (cur^1)
                && color(i + 2, j - 2) == 0
            ) {
                cout << "Yes" << '\n';
                return;
            }
            if (
                   color(i, j) == cur
                && color(i - 1, j - 1) == (cur^1)
                && color(i - 2, j - 2) == 0
            ) {
                cout << "Yes" << '\n';
                return;
            }
            if (
                   color(i, j) == cur
                && color(i - 1, j + 1) == (cur^1)
                && color(i - 2, j + 2) == 0
            ) {
                cout << "Yes" << '\n';
                return;
            }
        }

    }
    cout << "No" << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}