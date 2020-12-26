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
 
ll n;
ll a, b;

 
int solve() {
    if (!(cin >> n >> a >> b))
        return 1;
    if (a > b)
        swap(a, b);

    ll can = min(b - a, n);
    ll ans = can * (2 * a + can - 1) / 2;
    n -= can;
    if (n > 0){
        ll t = n / 2;
        ans += t * (2 * b + t - 1);
        if (n % 2)
            ans += b + t;
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
