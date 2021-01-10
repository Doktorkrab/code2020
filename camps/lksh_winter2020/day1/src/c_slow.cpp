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
 
int n;
string s;
 
int solve() {
    if (!(cin >> s))
        return 1;
    n = SZ(s);
    int ans = 0;
    for (int l = 1; l <= n; l++){
        for (int i = 0; i + 2 * l <= n; i++){
            if (s.substr(i, l) == s.substr(i + l, l)){
//                cout << l << ' ' << s.substr(i, l) << '\n';
                ans = l;
                break;
            }
        }
    }
    cout << ans * 2 << '\n';
    return 0;
}
 
signed main() {
//#ifdef LOCAL
//    freopen("c.in", "r", stdin);
//#endif
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
