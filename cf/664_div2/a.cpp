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
 
int r, g, b, w;

 
int solve() {
    if (!(cin >> r >> g >> b >> w))
        return 1;
    int have = (r % 2) + (g % 2) + (b % 2) + (w % 2);
    if (have <= 1){
        cout << "YES\n";
        return 0;
    }
    if (min({r, g, b}) > 0)
        r--, g--, b--, w += 3;
    have = (r % 2) + (g % 2) + (b % 2) + (w % 2);
    if (have <= 1){
        cout << "YES\n";
        return 0;
    }
    cout << "No\n";
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
