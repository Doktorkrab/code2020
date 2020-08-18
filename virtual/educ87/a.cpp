#include <bits/stdc++.h>
#include <ostream>
 
using namespace std;
using ll = long long;

#define int ll

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
    a -= b;
    if (a <= 0){
        cout << b << '\n';
        return 0;
    }
    int diff = c - d;
    if (diff <= 0){
        cout << "-1\n";
        return 0;
    }
    cout << b + (a + diff - 1) / diff * c << '\n';
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