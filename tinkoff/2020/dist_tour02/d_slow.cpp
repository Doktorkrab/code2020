#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;


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

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++) {
        cin >> rays[i].first >> rays[i].second;
    }
    int q;
    cin >> q;
    cout << setprecision(20) << fixed;
    bool was = true;
    for (int i = 0; i < q; i++) {
        double x = -1;
        int c, d;
        cin >> c >> d;
        if (!was) {
            c ^= (1U << (29)) - 1U;
            d ^= (1U << 29) - 1;
        }
        for (int j = 0; j < n; j++) {
            auto[a, b] = rays[j];
            if (c == a)
                continue;
            double x_now = 1. * (b - d) / (c - a);
            x = max(x, x_now);
        }
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
