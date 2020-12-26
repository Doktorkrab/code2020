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
 
long long k;

 
int solve() {
    if (!(cin >> k))
        return 1;
    long long com = 25 + k / 100;
    long long kek = k % 100;
    if (com < 100) {
        kek = 0;
        com = 100;
    }
    if (com > 2000 || (com == 2000 && kek != 0)) {
        kek = 0;
        com = 2000;
    }
    cout << com << '.';
    if (kek <= 9) {
        cout << 0;
    }
    cout << kek << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
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
