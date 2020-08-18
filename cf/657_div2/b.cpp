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
 
int l, r;
ll m;

 
int solve() {
    if (!(cin >> l >> r >> m))
        return 1;
    // cout << m - r + l << ' ' << m + r - l << '\n';
    for (int i = l; i <= r; i++){
        int cnt = max(0LL, (m + r - l)) / i - max(0LL, (m - r + l) - 1) / i;
        if (cnt > 0){

            int have = m - (m + r - l) / i * i;
            // cout << i << ' ' << have << '\n';
            int b, c;
            if (have >= 0){
                c = l;
                b = have + l;
            }
            else {
                b = l;
                c = -have + l;
            }
            cout << i << ' ' << b << ' ' << c << '\n';
            return 0;
        }
    }
    assert(0);
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