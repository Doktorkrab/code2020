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
const int MAXN = 1505;
int a[MAXN][MAXN];
int dp[2][MAXN][MAXN]; // left/right, prefix, last
int mn[2][MAXN]; 
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                dp[i][j][k] = 1e9;
    dp[0][0][0] = dp[1][0][0] = 0;
    dp[0][1][0] = a[1][0];
    dp[1][1][0] = a[0][1];
    for (int i = 2; i < n; i++){
        int have = 0;
        for (int j = 0; j < i; j++){
            dp[1][i][j] = dp[1][i - 1][j] + a[i - 1][i];
            dp[0][i][j] = dp[0][i - 1][j] + a[i][i - 1];
        }
        for (int j = i - 2; j >= 0; j--){
            //for (int k = 0; k < j || (j == 0 && k == 0); k++)
            for (int k : {0, j - 1})
                if (k >= 0)
                    dp[1][i][i - 1] = min(dp[1][i][i - 1], dp[1][j][k] + have + a[j + 1][k] + a[j][i]);
            have += a[j + 1][j];
        }
        have = 0;
        for (int j = i - 2; j >= 0; j--){
            //for (int k = 0; k < j || (j == 0 && k == 0); k++)
            for (int k : {0, j - 1})
                if (k >= 0)
                    dp[0][i][i - 1] = min(dp[0][i][i - 1], dp[0][j][k] + have + a[k][j + 1] + a[i][j]);
            have += a[j][j + 1];
        }
    }
    //for (int i = 0; i < 2; i++){
        //for (int j = 0; j < n; j++){
            //cout << j + 1 << ": ";
            //for (int k = 0; k < j; k++)
                //cout << dp[i][j][k] << " ";
            //cout << '\n';
        //}
        //cout << '\n';
    //}
    int ans = TMAX(int);
    for (int i = 0; i + 1 < n; i++)
        ans = min(ans, min(dp[0][n - 1][i], dp[1][n - 1][i]));
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
