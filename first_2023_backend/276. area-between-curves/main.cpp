#include <bits/stdc++.h>
using namespace std;
#define all(a) (a).begin(), (a).end()
#define double long double

void solve() {
    int n, m;
    cin >> n >> m;
    vector<double> l(n + 1);
    for (int i = 0; i <= n; ++i) {
        cin >> l[i];
    }
    vector<double> fa(n);
    vector<double> fb(n);
    vector<double> fc(n);
    for (int i = 0; i < n; ++i) {
        cin >> fa[i] >> fb[i] >> fc[i];
    }

    vector<double> r(m + 1);
    for (int i = 0; i <= m; ++i) {
        cin >> r[i];
    }
    vector<double> ga(m);
    vector<double> gb(m);
    vector<double> gc(m);
    for (int i = 0; i < m; ++i) {
        cin >> ga[i] >> gb[i] >> gc[i];
    }
    vector<double> p(n + m + 2);
    merge(all(l), all(r), p.begin());
    
    double ans = 0;
    for (int i = 0; i + 1 < n + m + 2; ++i) {
        int lo_f = 0;
        int hi_f = n;
        while (hi_f - lo_f > 1) {
            int mid = (lo_f + hi_f) / 2;
            if (l[mid] <= p[i])
                lo_f = mid;
            else
                hi_f = mid;
        }
        int lo_g = 0;
        int hi_g = m;
        while (hi_g - lo_g > 1) {
            int mid = (lo_g + hi_g) / 2;
            if (r[mid] <= p[i])
                lo_g = mid;
            else
                hi_g = mid;
        }
        double a = fa[lo_f] - ga[lo_g];
        double b = fb[lo_f] - gb[lo_g];
        double c = fc[lo_f] - gc[lo_g];

        double aa = (a / 3.0);
        double bb = (b / 2.0);
        double cc = (c / 1.0);
        auto evaluate = [&](double x) {
            return aa*x*x*x + bb*x*x + cc*x;
        };
        vector<double> points;
        points.push_back(p[i]);
        if (a != 0) {
            double D = b*b - 4*a*c;
            if (D >= 0) {
                double r1 = (-b - sqrtl(D)) / (2.0 * a);
                double r2 = (-b + sqrtl(D)) / (2.0 * a);
                if (p[i] <= r1 && r1 <= p[i + 1])
                    points.push_back(r1);
                if (p[i] <= r2 && r2 <= p[i + 1])
                    points.push_back(r2);
                // cout << r1 << ' ' << r2 << '\n';
            }
        } else {
            if (b != 0) {
                double r1 = -c / b;
                if (p[i] <= r1 && r1 <= p[i + 1])
                    points.push_back(r1);
            }
        }
        points.push_back(p[i + 1]);
        sort(all(points));
        for (int k = 0; k + 1 < points.size(); ++k) {
            // cout << evaluate(points[k + 1]) - evaluate(points[k]) << '\n';
            ans += abs(evaluate(points[k + 1]) - evaluate(points[k]));
        }
    } 
    cout << ans << '\n';
}

signed main() {
    cout.precision(10);cout.setf(ios_base::fixed);
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}