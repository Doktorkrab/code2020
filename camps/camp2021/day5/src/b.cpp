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
#define int ll
int n, W;
const int MAXW = 1e5 + 7;
const int INF = 1e18;
int dp[MAXW];
 
int solve() {
    if (!(cin >> n >> W))
        return 1;
    fill(dp, dp + MAXW, -INF);
    dp[0] = 0;
    for (int i = 0; i < n; i++){
        int w, v;
        cin >> w >> v;
        for (int j = W; j - w >= 0; j--)
            dp[j] = max(dp[j], dp[j - w] + v);
    }
    cout << *max_element(dp, dp + W + 1) << '\n';
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
