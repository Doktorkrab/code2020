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
const int MAXN = 3e3 + 3;
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
        for (int j = 0; j < n; j++){
            long double tt = 1.L * abs(x[j] - p) / u;
            long double nxt = ceil(max(0.L, (tt + t - 1.L * x[j] / v) / w)) * w + 1.L * x[j] / v;
            mx = min(mx, 1.L * (x[n - 1] - x[j]) / v + nxt);
//            cout << j << " " << 1.L * (x[n - 1] - x[j]) / v + nxt << ' ' << nxt - 1.L * x[j] / v << '\n';
//            cout << (nxt - 1.L * x[j] / v) + 1.L * x[n - 1] / v << '\n';
        }
        cout << mx << '\n';
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
