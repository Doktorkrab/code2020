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
const int MAXN = 1.5e5 + 3;
int x[MAXN];
int w, v, q;

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++){
        cin >> x[i];
    }
    cin >> w >> v >> q;
    cout << setprecision(20) << fixed;
    for (int i = 0; i < q; i++){
        int p, t, u;
        cin >> p >> t >> u;
        long double mx = t + 1.L * (x[n - 1] - p) / u;
        int pos = lower_bound(x, x + n, p) - x;
        long double tt = 1.L * abs(x[pos]- p) / u;
        long double nxt = ceil(max(0.L, (tt + t - 1.L * x[pos] / v) / w)) * w;
        if (pos > 0){
            pos--;
            tt = 1.L * abs(x[pos]- p) / u;
            nxt = min(nxt, ceil(max(0.L, (tt + t - 1.L * x[pos] / v) / w)) * w);
        }
//        cout << nxt << '\n';
        cout << min(mx, nxt + 1.L * x[n - 1] / v) << '\n';
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
