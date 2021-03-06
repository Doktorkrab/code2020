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
 
int n, m, sale;
const int MAXN = 305;
const int INF = 1e9 + 7;
int dp[MAXN][MAXN][MAXN];
int arr[MAXN];
 
int solve() {
    if (!(cin >> n >> m >> sale))
        return 1;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            for (int k = 0; k<= m; k++)
                dp[i][j][k] = INF;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    for (int i = 0; i <= m; i++)
        dp[0][0][i] = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j <= m && j <= i + 1; j++)
            for (int k = 0; j + k <= m && k < n - i; k++){
                int mn = INF;
                if ((i - j + 1) % sale == 0)
                    mn = dp[i][j][k];
                else
                    mn = dp[i][j][k] + arr[i];
                if (j > 0 && (n - k) % sale == 0)
                    mn = min(dp[i][j - 1][k + 1], mn);
                else if (j > 0)
                    mn = min(dp[i][j - 1][k + 1] + arr[i], mn);
                dp[i + 1][j][k] = mn;
            }
    }
//    for (int i = 0; i <= n; i++){
//        for (int j = 0; j <= m; j++)
//            for (int k = 0; j + k <= m; k++)
//                cout << dp[i][j][k] << " \n"[j + k == m];
//        cout << '\n';
//    }
    int ans = INF;
    for (int i = 0; i <= m; i++)
        ans = min(ans, dp[n][i][0]);
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
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}
