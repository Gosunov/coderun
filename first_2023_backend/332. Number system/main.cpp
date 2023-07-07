#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()
#define int long long

bool is_digit(char c) {
    return ('0' <= c && c <= '9') || ('A' <= c && c <= 'Z'); 
}

int value(char c) {
    assert(is_digit(c));
    if ('0' <= c && c <= '9') {
        return c - '0';
    }
    if ('A' <= c && c <= 'Z') {
        return c - 'A' + 10;
    }
    assert(false);
    return 0;
}

string normalize(const string& s) {
    string res = "+";
    int n = s.size();
    bool was_eq = false;
    for (int i = 0; i < n; ++i) {
        if (s[i] == ' ') {
            continue;
        } else if (s[i] == '=') {
            was_eq = true;
            res += '-';
        } else if (s[i] == '+') {
            res += was_eq ? '-' : '+'; 
        } else if (s[i] == '-') {
            res += was_eq ? '+' : '-'; 
        } else {
            res += s[i];
        }
    }
    return res;
}

vector<string> split_to_numbers(const string& s) {
    int n = s.size();
    vector<string> res;
    for (int i = 0; i < n; ++i) {
        int j = i + 1;
        while (j < n && s[j] != '+' && s[j] != '-')
            j += 1;
        string number = s.substr(i, j - i);
        res.push_back(number);

        i = j - 1;
    }
    return res;
}

vector<int> numbers_to_poly(const vector<string>& numbers) {
    int poly_size = 0;
    for (string number : numbers) {
        poly_size = max(poly_size, (int)number.size() - 1);
    }
    vector<int> poly(poly_size);
    for (string number : numbers) {
        reverse(all(number));
        int n = number.size();
        int sign = number.back() == '+' ? 1 : -1;
        for (int i = 0; i < n - 1; ++i) {
            poly[i] += value(number[i]) * sign;
        }
    }
    return poly;
}

bool is_root(const vector<int>& poly, int x) {
    const int mod = 1000000007;
    int n = poly.size();
    int res = 0;
    int xx = 1;
    for (int i = 0; i < n; ++i) {
        res += (mod + (poly[i] % mod * xx % mod)) % mod;
        if (res >= mod) res -= mod;
        xx = (xx * x) % mod;
    }
    // cout << res << '\n';
    return res == 0;
}

void solve() {
    string s;
    getline(cin, s);
    s = normalize(s);

    vector<string> numbers = split_to_numbers(s);
    vector<int> poly = numbers_to_poly(numbers);
    
    int max_digit = 1;
    for (char c : s) {
        if (is_digit(c))
            max_digit = max(max_digit, value(c));
    }

    int c = 0;
    for (int i = 0; i < poly.size() && (c = poly[i]) == 0; ++i);
    c = abs(c);

    if (c == 0) {
        cout << (is_root(poly, max_digit + 1) ? max_digit + 1 : -1) << '\n';
        return;
    }

    int mnroot = 1e9;
    for (int x = 1; x * x <= c; ++x) {
        if (int y = c / x; x * y == c) {
            // cout << x << ' ' << y << '\n';
            if (x > max_digit && is_root(poly, x)) {
                mnroot = min(x, mnroot);
            }
            if (y > max_digit && is_root(poly, y)) {
                mnroot = min(y, mnroot);
            }
        }
    }
    
    cout << (mnroot == 1e9 ? -1 : mnroot) << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}