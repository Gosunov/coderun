#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()

const int maxn = 10005;
const int inf = 0x3f3f3f3f;

int n, m;

int**  table;
bool** is_delim;

int rows_count;
int cols_count;

int rows[maxn];
int cols[maxn]; 
// (rows[i], cols[j]) is coordinates of elementary cell (i, j) in table

void parse_table() {
    string s;
    getline(cin, s);
    for (int i = 0; i < n; ++i) {
        getline(cin, s);
        for (int j = 0; j < m; ++j){
            char c = s[j];
            if (c == '-' || c == '|' || c == '+')
                continue;
            int neighbour = min(table[i - 1][j], table[i][j - 1]);
            if (neighbour == inf) {
                table[i][j] = i * m + j;
                continue;
            }
            table[i][j] = neighbour;
        }
    }
    cin >> rows_count;
    rows[0] = 1;
    for (int i = 1; i <= rows_count; ++i) {
        cin >> rows[i];
        rows[i] = rows[i] + rows[i - 1] + 1;
    }

    cin >> cols_count;
    cols[0] = 1;
    for (int i = 1; i <= cols_count; ++i) {
        cin >> cols[i];
        cols[i] = cols[i] + cols[i - 1] + 1;
    }
    for (int i = 0; i <= rows_count; ++i) {
        int r = rows[i] - 1;
        for (int j = 0; j < m; ++j) {
            is_delim[r][j] = true;
        }
    }
    for (int i = 0; i <= rows_count; ++i) {
        int r = rows[i] - 1;
        for (int j = 0; j < m; ++j) {
            is_delim[r][j] = true;
        }
    }
    for (int j = 0; j <= cols_count; ++j) {
        int c = cols[j] - 1;
        for (int i = 0; i < n; ++i) {
            is_delim[i][c] = true;
        }
    }
}

void init() {
    table    = new int*[n];
    is_delim = new bool*[n];
    for (int i = 0; i < n; ++i) {
        table[i]    = new int[m];
        is_delim[i] = new bool[m];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            table[i][j]    = inf;
            is_delim[i][j] = false;
        }
    }
    parse_table();
}

void parse_coordinates(const string& s, int& i, int& j) {
    int p = 0;
    while ('A' <= s[p] && s[p] <= 'Z') {
        p++;
    }
    assert('1' <= s[p] && s[p] <= '9');
    string col = s.substr(0, p);
    string row  = s.substr(p);
    i = stoi(row) - 1;
    int w = 1;
    j = 0;
    reverse(all(col));
    for (char c : col) {
        j += (c - 'A' + 1) * w;
        w *= 26;
    }
    j -= 1;
}

bool is_ok(int i, int j) {
    return 0 <= i && i < n && 0 <= j && j < m;
}

bool occupied(int i, int j) {
    assert(is_ok(i, j));
    return table[i][j] != inf;
}

void print_table() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!occupied(i, j)) {
                bool has_horizontal = false;
                bool has_vertical   = false;
                has_vertical   |= is_ok(i - 1, j) && !occupied(i - 1, j);
                has_vertical   |= is_ok(i + 1, j) && !occupied(i + 1, j);
                has_horizontal |= is_ok(i, j - 1) && !occupied(i, j - 1);
                has_horizontal |= is_ok(i, j + 1) && !occupied(i, j + 1);
                if (has_horizontal && has_vertical) {
                    cout << '+';
                } else if (has_horizontal) {
                    cout << '-';
                } else if (has_vertical) {
                    cout << '|';
                } else {
                    assert(false);
                }
            } else {
                cout << ' ';
            }
        }
        cout << '\n';
    }
}

void split_dfs(int i, int j, int c1, int c2, vector<vector<bool> >& used) {
    if (is_delim[i][j]) {
        table[i][j] = inf;
        return;
    }
    if (used[i][j] || table[i][j] != c1) {
        return;
    }
    table[i][j] = c2;
    used[i][j] = true;
    if (is_ok(i - 1, j)) split_dfs(i - 1, j, c1, c2, used);
    if (is_ok(i + 1, j)) split_dfs(i + 1, j, c1, c2, used);
    if (is_ok(i, j - 1)) split_dfs(i, j - 1, c1, c2, used);
    if (is_ok(i, j + 1)) split_dfs(i, j + 1, c1, c2, used);

    if (is_ok(i + 1, j + 1)) split_dfs(i + 1, j + 1, c1, c2, used);
    if (is_ok(i + 1, j - 1)) split_dfs(i + 1, j - 1, c1, c2, used);
    if (is_ok(i - 1, j + 1)) split_dfs(i - 1, j + 1, c1, c2, used);
    if (is_ok(i - 1, j - 1)) split_dfs(i - 1, j - 1, c1, c2, used);

}

void split() {
    string c;
    cin >> c;
    int i1, j1;
    parse_coordinates(c, i1, j1);
    vector<vector<bool> > used(n, vector<bool>(m));
    int k = 0;
    int c1 = table[rows[i1]][cols[j1]];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!used[i][j] && !is_delim[i][j] && table[i][j] == c1) {
                k += 1;
                split_dfs(i, j, c1, i * m + j, used);
            }
        }
    }
    if (k == 1) {
        cout << "Can not split elementary cell" << '\n';
        return;
    }
    cout << "Split onto " << k << " cells" << '\n';
    print_table();
}

void merge_dfs(int i, int j, vector<vector<bool> >& used) {
    if (table[i][j] == inf) {
        return;
    }
    if (used[i][j]) {
        return;
    }
    used[i][j] = true;
    if (is_ok(i - 1, j)) merge_dfs(i - 1, j, used);
    if (is_ok(i + 1, j)) merge_dfs(i + 1, j, used);
    if (is_ok(i, j - 1)) merge_dfs(i, j - 1, used);
    if (is_ok(i, j + 1)) merge_dfs(i, j + 1, used);
}

void merge() {
    string c1, c2;
    cin >> c1 >> c2;
    int i1, j1, i2, j2;
    parse_coordinates(c1, i1, j1);
    parse_coordinates(c2, i2, j2);
    if (i1 * cols_count + j1 > i2 * cols_count + j2) {
        swap(i1, i2);
        swap(j1, j2);
    }
    int c1i = rows[i1];
    int c1j = cols[j1];
    int c2i = rows[i2];
    int c2j = cols[j2];

    if (table[c1i][c1j] == table[c2i][c2j]) {
        cout << "Can not merge cell with itself" << '\n';
        return;
    }
    vector<vector<bool> > used(n, vector<bool>(m));
    merge_dfs(c1i, c1j, used);
    merge_dfs(c2i, c2j, used);
    bool can_merge_vertical   = true;
    bool can_merge_horizontal = true;
    for (int i = 0; i < n; ++i) {
        int xo  = 0;
        int xox = 0; 
        for (int j = 0; j + 1 < m; ++j) {
            xo += used[i][j] == 1 && used[i][j + 1] == 0;
        }
        for (int j = 0; j + 2 < m; ++j) {
            xo += used[i][j] == 1 && used[i][j + 1] == 0 && used[i][j + 2] == 1;
        }
        if (xo == 1)
            can_merge_horizontal  = false;
        if (xo == 2)
            can_merge_horizontal &= xox == 1;
    }
    for (int j = 0; j < m; ++j) {
        int xo  = 0;
        int xox = 0; 
        for (int i = 0; i + 1 < n; ++i) {
            xo += used[i][j] == 1 && used[i + 1][j] == 0;
        }
        for (int i = 0; i + 2 < n; ++i) {
            xo += used[i][j] == 1 && used[i + 1][j] == 0 && used[i + 2][j] == 1;
        }
        if (xo == 1)
            can_merge_vertical  = false;
        if (xo == 2)
            can_merge_vertical &= xox == 1;
    }
    if (!can_merge_vertical && !can_merge_horizontal) {
        cout << "Can not merge unaligned cells" << '\n';
        return;
    }
    if (can_merge_vertical) {
        cout << "Merged vertically-aligned cells" << '\n';
        for (int j = 0; j < m; ++j) {
            int i = 0;
            while (i < n && !used[i][j]) {
                i += 1;
            }
            if (i == n)
                continue;
            while (used[i][j]) {
                i += 1;
            }
            used[i][j] = true;
            while (used[i][j]) {
                table[i][j] = table[i - 1][j];
                i += 1;
            }
        }
        print_table();
        return;
    }
    if (can_merge_horizontal) {
        cout << "Merged horizontally-aligned cells" << '\n';
        for (int i = 0; i < n; ++i) {
            int j = 0;
            while (j < m && !used[i][j]) {
                j += 1;
            }
            if (j == m)
                continue;
            while (used[i][j]) {
                j += 1;
            }
            used[i][j] = true;
            while (used[i][j]) {
                table[i][j] = table[i][j - 1];
                j += 1;
            }
        }
        print_table();
        return;
    }
}

void debug() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (table[i][j] == inf)
                printf("%3d", -1);
            else
                printf("%3d", table[i][j]);
        }
        cout << '\n';
    }
}

void solve() {
    cin >> n >> m;
    init();
    int q;
    cin >> q;
    while (q--) {
        string cmd;
        cin >> cmd;
        if (cmd == "merge") {
            merge();
        }
        if (cmd == "split") {
            split();
        }
    }
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}