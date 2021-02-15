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

int h, n, m, a, b;

int solve() {
    if (!(cin >> h >> n >> m >> a >> b))
        return 1;
    int afrom = (n + a - 1) / a;
    int ato = n;
    int bfrom = (m + b - 1) / b;
    int bto = m;
    if (afrom <= bfrom) {
        if (ato >= bfrom - 1) {
            cout << "YES\n";
            if (h == 1) {
                if (ato >= bfrom)
                    solve(bfrom, bfrom);
                else
                    solve(ato, bfrom);

            }
        } else
            cout << "NO\n";
        return 0;
    }
    if (bto >= afrom - 1) {
        cout << "YES\n";
        if (h == 1) {

        }
    } else
        cout << "NO\n";
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
#endif
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
