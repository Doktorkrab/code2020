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
 
ll a, b, c, n;

 
int solve() {
    if (!(cin >> a >> b >> c >> n))
        return 1;
    if (b > 7 * a)
        b = 7 * a;
    if (c > 4 * b)
        c = 4 * b;
    ll ans = n / 28 * c;
    n %= 28;
    ll n1 = n / 7 * b;
    n %= 7;
    ll n2 = n * a;
    n1 += min(n2, b);
    ans += min(n1, c);
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