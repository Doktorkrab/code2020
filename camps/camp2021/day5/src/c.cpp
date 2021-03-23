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
 
int n, W;
const int MAXV = 1e5 + 7;
const ll INF = 1e18;
ll dp[MAXV];
 
int solve() {
    if (!(cin >> n >> W))
        return 1;
    fill(dp, dp + MAXV, INF);
    dp[0] = 0;
    for (int i = 0; i < n; i++){
        ll w, v;
        cin >> w >> v;
        for (int j = MAXV - 1; j - v >= 0; j--){
            dp[j] = min(dp[j], dp[j - v] + w);
        }
    }
    for (int i = MAXV - 1; i >= 0; i--){
        if (dp[i] <= W){
            cout << i << '\n';
            break;
        }
    }
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
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
