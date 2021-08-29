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


ll find(ll x) {
    ll l = 0, r = 1e9 + 7;
    while (r - l > 1) {
        ll m = (l + r) / 2;
        if (m * m > x)
            r = m;
        else
            l = m;
    }
    return l;
}

int solve() {
    ld xx, yy, rr;
    if (!(cin >> xx >> yy >> rr))
        return 1;
    ll x = (ll) (xx * 10000);
    ll y = (ll) (yy * 10000);
    ll r = (ll) (rr * 10000);
    ll r0 = ((ll) rr) + 10;
    ll y0 = (ll) yy;
    ll ans = 0;
    for (ll i = -r0; i <= r0; i++) {
        ll l1 = (y0 + i) * 10000 - y;
        if (r * r < l1 * l1)
            continue;
        ll l = find(r * r - l1 * l1);
        ans += max(0LL, ((x + l) / 10000) - ((x - l + 10000 - 1) / 10000) + 1);
    }
    cout << ans << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("f2.in", "r", stdin);
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
