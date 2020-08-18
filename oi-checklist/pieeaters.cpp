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
 
const int MAXN = 305;
int n, m;
int dp[MAXN][MAXN];
int mx[MAXN][MAXN][MAXN];
int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < m; i++){
        int w, l, r;
        cin >> w >> l >> r;
        for (int j = l; j <= r; j++)
            mx[j][l][r] = max(mx[j][l][r], w);
    }

    for (int l = 1; l <= n; l++)
        for (int i = 1; i + l - 1 <= n; i++){
            for (int k = i; k < i + l; k++)
                mx[k][i][i + l - 1] = max(mx[k][i][i + l - 1], max(mx[k][i + 1][i + l - 1], mx[k][i][i + l - 2]));
        }

    for (int l = 1; l <= n; l++)
        for (int i = 1; i + l - 1 <= n; i++){
            // cout << i << ' ' << i + l - 1 << '\n';
            for (int split = i; split < i + l; split++){
                // cout << split << '\n';
                dp[i][i + l - 1] = max(dp[i][i + l - 1], dp[i][split - 1] + dp[split + 1][i + l - 1] + mx[split][i][i + l - 1]);
                dp[i][i + l - 1] = max(dp[i][i + l - 1], dp[i][split] + dp[split + 1][i + l - 1]);
            }
        }

    // for (int i = 1; i <= n; i++)
    //     for (int j = 1; j <= n; j++)
    //         cout << dp[i][j] << " \n"[j == n];
    cout << dp[1][n] << '\n';
    return 0;
}
 
signed main() {
#ifndef LOCAL
    freopen("pieaters.in", "r", stdin);
    freopen("pieaters.out", "w", stdout);
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