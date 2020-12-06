#include <bits/stdc++.h>
#include <ostream>
 
using namespace std;
using ll = long long;
using ld = long double;


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

const int MAXN = 2e3 + 7;
int t, w;
int cy, cv;
int n;
int poses[MAXN];
int k;
int cars[MAXN];
 
int solve() {
    if (!(cin >> t >> w >> cy >> cv >> n))
        return 1;
    for (int i = 1; i <= n; i++)
        cin >> poses[i];
    poses[0] = -1e9;
    poses[n + 1] = 1e9;
    cin >> k;
    for (int i = 0; i < k; i++)
        cin >> cars[i];
    ld ans = 0;
    cout << fixed << setprecision(20);
    for (int j = 0; j < k; j++) {
        for (int i = 0; i <= n; i++){
            int x2 = poses[i] + w;
            int x3 = poses[i + 1];
            int x1 = cars[j];
            if (cy * cv == -1) {
                if (2 * x2 - x1 <= 0 && 0 <= 2 * x3 - x1)
                    ans += t;
                continue;
            }
            long double l = max(0.L, ((cy + 1) * x2 - cy * x1) * 1.L / (1 + cy * cv));
            long double r = min(((cy + 1) * x3 - cy * x1 * 1.L) * 1.L / (1 + cy * cv), t * 1.L);
            cout << i << ' ' << j << ' ' << max(r - l, 0.L) << ' ' << l << ' ' << r << '\n';
            ans += max(r - l, 0.L);
        }
    }
    cout << ans << '\n';
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
