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
 
int n, m, k;
using ll = long long;
const int MAXN = 2e4 + 7;
ll dp[MAXN];
ll arr[MAXN];
int solve() {
    if (!(cin >> n >> m >> k))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    dp[0] = 0;
    for (int i = 0; i < n; i++){
        ll mn = arr[i];
        ll mx = arr[i];
        dp[i + 1] = dp[i] + k + mx - mn;
        for (int j = i - 1; j >= 0 && (i - j + 1) <= m; j--){
            mn = min(arr[j], mn);
            mx = max(arr[j], mx);
            dp[i + 1] = min(dp[i + 1], dp[j] + k + (i - j + 1) * (mx - mn));
        }
    }
//    for (int i = 0; i <= n; i++)
//        cout << dp[i] << " \n"[i == n];
    cout << dp[n] << '\n';
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
