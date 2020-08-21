
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

 
int solve() {
    if (!(cin >> n))
        return 1;
    int mn = n + 1;
    for (int i = 0; i < (1 << n); i++){
        bool good = true;
        for (int j = 0; j < n; j++){
            int prev = (j - 1 + n) % n;
            int nxt = (j + 1) % n;
            int cnt = 0;
            if ((i >> prev) & 1)
                cnt++;
            if (!((i >> nxt) & 1))
                cnt++;
            if (cnt == 0 || cnt == 2)
                continue;
            if ((!((i >> j) & 1) && ((i >> prev) & 1)) || (((i >> j) & 1) && (!((i >> nxt) & 1))))
                continue;
            good = false;
            break;
        }
        if (good)
            mn = min(mn, n - __builtin_popcount(i));
    }
    cout << mn << '\n';
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
