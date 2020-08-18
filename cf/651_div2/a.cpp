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

const int MAXN = 1e6 + 7;
int n;
int ans[MAXN];

 
int solve() {
    if (!(cin >> n))
        return 1;
    cout << ans[n] << '\n';
    return 0;
}
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
   cin >> tests;
   ans[0] = 1;
    for (int i = 1; i < MAXN; i++){
        ans[i] = ans[i - 1];
        for (int f = 2; 1LL * f * f <= i; i++){
            if (i % f == 0){
                ans[i] = max(ans[i], i / f);
                break;
            }
        }
    }
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}