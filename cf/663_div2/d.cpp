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
 
int n, m;
const int MAXN = 1e6;
const int INF = 1e9;
string arr[MAXN];
int dp[1 << 3][MAXN];
inline bool check(int m1, int m2){
    if (n == 2)
        return (__builtin_popcount(m1) + __builtin_popcount(m2)) % 2 == 1;
    return (__builtin_popcount(m1 & 3) + __builtin_popcount(m2 & 3)) % 2 == 1 && (__builtin_popcount(m1 & 6) + __builtin_popcount(m2 & 6)) % 2 == 1;
}
int solve(){
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    if (n == 1){
        cout << "0\n";
        return 0;
    }
    if (n > 3){
        cout << "-1\n";
        return 0;
    }
    for (int i = 0; i < m; i++){
        int now = 0;
        for (int j = 0; j < n; j++)
            now |= (1 << j) * (arr[j][i] == '1');
        for (int mask = 0; mask < (1 << n); mask++){
            dp[mask][i] = INF;
            if (i == 0){
                dp[mask][i] = __builtin_popcount(now ^ mask);
                continue;
            }
            for (int prev = 0; prev < (1 << n); prev++){
                if (!check(mask, prev))
                    continue;
                dp[mask][i] = min(dp[mask][i], dp[prev][i - 1] + __builtin_popcount(now ^ mask));
            }
        }
    }
    // for (int i = 0; i < (1 << n); i++)
    //     for (int j = 0; j < m; j++)
    //     cout << dp[i][j] << " \n"[j + 1 == m]; 
    int ans = INF;
    for (int i = 0; i < (1 << n); i++)
        ans = min(ans, dp[i][m - 1]);
    if (ans == INF)
        cout << "-1\n";
    else
        cout << ans << '\n';
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
// #ifdef LOCAL
        // cout << "------------------------------\n";
// #endif
    }
}