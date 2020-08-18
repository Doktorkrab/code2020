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

const int MAXN = 32;
const ll INF = 1e18 + 7;
int n, m;
ll arr[MAXN][MAXN];
ll dp[MAXN][MAXN];
ll sum[MAXN];
ll computed_maxs[MAXN];
int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> arr[i][j];
    ll ans = INF;
    // for (int i = 0; i < n; i++)
    //     for (int j = 0; j < n; j++)
    //         cout << arr[i][j] << " \n"[j == n - 1];
    for (int mask = 0; mask < (1 << n); mask++){
        int can = m - __builtin_popcount(mask);
        if (can < 0)
            continue;
        for (int i = 0; i <= can; i++)
            for (int j = 0; j < n; j++)
                dp[i][j] = INF;

        for (int i = 0; i < n; i++){
            for (int j = 0; j <= __builtin_popcount(mask); j++)
                    sum[j] = 0;
            for (int j = 0; j < n; j++)
                computed_maxs[j] = 0;
            for (int j = i; j >= 0; j--){
                int now = 0;
                for (int k = 0; k < n; k++){
                    sum[now] += arr[j][k];
                    if ((mask >> k) & 1)
                        now++;
                }
                computed_maxs[j] = (*max_element(sum, sum + __builtin_popcount(mask) + 1));
            }

            dp[0][i] = computed_maxs[0];
            for (int took = 1; took <= can; took++)
                for (int j = i; j >= 1; j--)
                    dp[took][i] = min(dp[took][i], max(dp[took - 1][j - 1],computed_maxs[j]));
        }
        for (int i = 0; i <= can; i++)
            ans = min(ans, dp[i][n - 1]);
        // cout << mask << ": \n";
        // for (int j = 0; j < n; j++)
        //     for (int i = 0; i <= can; i++)
        //         cout << dp[i][j] << " \n"[i == can];
        // cout << '\n';
    }
    cout << ans << '\n';
    return 0;
}
 
signed main() {
#ifndef LOCAL
    freopen("partition.in", "r", stdin);
    freopen("partition.out", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
//    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
// #ifdef LOCAL
//         cout << "------------------------------\n";
// #endif
    }
}