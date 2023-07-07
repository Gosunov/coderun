#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()
#define int long long
#define double long double

int normalize(int amount, string measure) {
    if (measure == "kg")
        return amount * 1000;
    if (measure == "l")
        return amount * 1000;
    if (measure == "tens")
        return amount * 10;
    return amount;
}

void solve() {
    int n;
    cin >> n;

    vector<string> products;
    unordered_map<string, int> product_cnt;
    unordered_map<string, unordered_map<string, int> > product_ingredients;

    for (int j = 0; j < n; ++j) {
        string product;
        cin >> product;
        cin >> product_cnt[product];
        int k;
        cin >> k;
        for (int i = 0; i < k; ++i) {
            string ingredient;
            int amount;
            string measure;
            cin >> ingredient >> amount >> measure;
            amount = normalize(amount, measure);
            product_ingredients[product][ingredient] = amount;
        }
        products.push_back(product);
    }

    unordered_map<string, int> need;
    for (auto [product, ingredients] : product_ingredients) {
        for (auto [ingredient, amount] : ingredients) {
            need[ingredient] += amount * product_cnt[product];
        }
    }

    vector<string> ingredients;
    int spent = 0;
    unordered_map<string, int> bought;
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        string ingredient;
        int price;
        int amount;
        string measure;
        cin >> ingredient >> price >> amount >> measure;
        amount = normalize(amount, measure);

        bought[ingredient] = (need[ingredient] + amount - 1) / amount;
        spent += price * bought[ingredient];

        ingredients.push_back(ingredient);
    }

    cout << spent << '\n';
    for (string ingredient : ingredients) {
        cout << ingredient << ' ' << bought[ingredient] << '\n';
    }

    int m;
    cin >> m;

    unordered_map<string, double> ingredient_a;
    unordered_map<string, double> ingredient_b;
    unordered_map<string, double> ingredient_c;
    unordered_map<string, double> ingredient_d;

    for (int i = 0; i < m; ++i) {
        string ingredient;
        int amount;
        string measure;
        cin >> ingredient >> amount >> measure;

        amount = normalize(amount, measure);

        double a, b, c, d;
        cin >> a >> b >> c >> d;
        ingredient_a[ingredient] = a / (double)amount;
        ingredient_b[ingredient] = b / (double)amount;
        ingredient_c[ingredient] = c / (double)amount;
        ingredient_d[ingredient] = d / (double)amount;
    }

    for (string product : products) {
        double a = 0;
        double b = 0;
        double c = 0;
        double d = 0;
        for (auto [ingredient, amount] : product_ingredients[product]) {
            a += ingredient_a[ingredient] * amount;
            b += ingredient_b[ingredient] * amount;
            c += ingredient_c[ingredient] * amount;
            d += ingredient_d[ingredient] * amount;
        }
        cout << product << ' ' << a << ' ' << b << ' ' << c << ' ' << d << '\n';
    }
}

signed main() {
    cout.precision(4),cout.setf(ios_base::fixed);
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}