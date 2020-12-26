#include <bits/stdc++.h>
#include <ostream>
 
using namespace std;
using ll = long long;
using ull = unsigned long long;

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
 
ll n, k;

 
int solve() {
    if (!(cin >> n >> k))
        return 1;
    ll kek = n / k;
    ll ans = TMAX(ll);
    for (ll i = -2; i <= 2; i++){
        ll t = max(0LL, (ll)(kek + i));
        ans = min(ans, (t * k) ^ n);
    }
    cout << ans << '\n';
    return 0;
}
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}
