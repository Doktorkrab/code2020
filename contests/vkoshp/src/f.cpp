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
 
int a, b, c, d;

 
int solve() {
    if (!(cin >> a >> b >> c >> d))
        return 1;
    if (c < 0 && d >= 10){
        cout << "A storm warning for tomorrow! Be careful and stay home if possible!\n";
    }
    else if (c < a) {
        cout << "MCHS warns! Low temperature is expected tomorrow.\n";
    } else if (d > b) {
        cout << "MCHS warns! Strong wind is expected tomorrow.\n";
    } else{
        cout << "No message\n";
    }
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("f.in", "r", stdin);
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
