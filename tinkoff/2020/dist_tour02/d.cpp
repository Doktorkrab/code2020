#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;
using ld = long double;

#define double ld

#define SZ(x) (int)((x).size())
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()

#define TMAX(type) numeric_limits<type>::max()
#define TMIN(type) numeric_limits<type>::min()
#ifdef LOCAL
#define ass(X) assert(X)
#else
#define ass(X) {}
#endif

int n;
const int MAXN = 5e4 + 7;
const double EPS = 1e-6;
pair<int, int> rays[MAXN];
pair<int, int> rays1[MAXN];
pair<int, int> rays2[MAXN];

double intersect(pair<int, int> a, pair<int, int> b){
    auto [at1, bt1] = a;
    auto [at2, bt2] = b;
    double a1 = 1. / at1;
    double a2 = 1. / at2;
    double b1 = 1. * -bt1 / at1;
    double b2 = 1. * -bt2 / at2;
    return 1. * (b2 - b1) / (a1 - a2);
}

struct CHT {
    vector<pair<int, int>> stack_lines;
    vector<double> inter_points;
    void insert(pair<int, int> nw) {
        while (!stack_lines.empty()) {
            auto lst_l = stack_lines.back();
            auto lst_p = inter_points.back();
            cerr << SZ(stack_lines) << '\n';
            double in = intersect(nw, lst_l);
            if (in > lst_p) {
                stack_lines.push_back(nw);
                inter_points.push_back(in);
                return;
            }
            stack_lines.pop_back();
            inter_points.pop_back();
        }
        stack_lines.push_back(nw);
        inter_points.push_back(-1e9);
    }

    double get(int x, int ex) {
        int l = 0, r = SZ(stack_lines);
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (inter_points[m] < x)
                l = m;
            else
                r = m;
        }
        if (stack_lines[l].first - ex == 0)
            return -1;
//        cout << "!" << stack_lines[l].first << ' ' << stack_lines[l].second << '\n';
        return 1. * (x - stack_lines[l].second) / (stack_lines[l].first - ex);
    }
};
int solve() {
    if (!(cin >> n))
        return 1;
    int pnt = 0;
    int pnt1 = 0;
    const int KEK = (1 << 29) - 1;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        rays[i] = {a, b};
        if (a != 0)
            rays1[pnt++] = {a, b};
        if (a - KEK != 0)
            rays2[pnt1++] = {a - KEK, b};
    }
//    n = pnt;
    sort(rays1, rays1 + n, [&](const pair<int, int>& a, const pair<int, int>& b){
        return 1. / a.first < 1. / b.first;
    });
    sort(rays2, rays2 + n, [&](const pair<int, int>& a, const pair<int, int>& b){
        return 1. / a.first < 1. / b.first;
    });
//    reverse(rays, rays + n);
    CHT kek, kek1;
    for (int i = 0; i < pnt; i++) {
        kek.insert(rays1[i]);
//        cout << rays[i].first << ' ' << rays[i].second << "!\n";
    }
    for (int i = 0; i < pnt1; i++)
        kek1.insert(rays2[i]);
//    for (auto [a, b] : kek.stack_lines)
//        cout << a << ' ' << b << '\n';
//    for (double x : kek.inter_points)
//        cout << x << ' ';
//    cout << '\n';
    int q;
    cin >> q;
    cout << setprecision(20) << fixed;
    bool was = true;
    for (int i = 0; i < q; i++) {
        double x = -1;
        int c, d;
        cin >> c >> d;
        int wasc = c;
        if (!was) {
            c ^= (1U << (29)) - 1U;
            d ^= (1U << 29) - 1;
        }
        if (c == 0)
            x = kek.get(d, 0);
        if (c == KEK)
            x = kek1.get(d, 0);
        for (int j = 0; j < n && wasc != 0; j++) {
            auto[a, b] = rays[j];
            if (c == a)
                continue;
            double x_now = 1. * (b - d) / (c - a);
            x = max(x, x_now);
        }
//        cout << x << '\n';
        if (x < EPS) {
            cout << "No cross\n";
            was = false;
        } else {
            cout << x << '\n';
            was = true;
        }
    }
    return 0;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
//    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}
