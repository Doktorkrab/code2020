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
 
int n, a, b;
int now = 0;

 
int solve() {
    if (!(cin >> n >> b >> a))
        return 1;
    now = 1;
    while (n >= 0){
        int took = gcd(n, a);
//        cout << n << ' ' << took << ' ' << now << '\n';
        if (took > n){
            cout << now << '\n';
            return 0;
        }
        n -= took;
        swap(a, b);
        now ^= 1;
    }
    cout <<  "jej\n";
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
