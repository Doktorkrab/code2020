#include <bits/stdc++.h>
#include <ostream>
 
using namespace std;
using ll = long long;
#define int ll

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
string s;
const int MAXN = 1005;
int dp[MAXN][MAXN]; // (i, A-bal)
int solve() {
    if (!(cin >> s))
        return 1;
    n = SZ(s);
    int bal = 0;
    dp[0][0] = 1;
    for (int i = 0; i < n; i++){
        if (s[i] == '('){
            for (int j = 0; j <= n; j++){
                dp[i + 1][j] = 0;
                // cout << i << ' ' << j << ' ' << (j - 1 >= 0) << ' ' << (bal - j >= 0) << '\n'; 
                // cout << '\t' << dp[i][j - 1] << ' ' << dp[i][j] << '\n';
                if (j - 1 >= 0)
                    dp[i + 1][j] += dp[i][j - 1];
                if (bal - j >= 0)
                    dp[i + 1][j] += dp[i][j];
                dp[i + 1][j] %= 2012;
                // cout << dp[i + 1][j] << '\n';
            }
            bal++;
        }
        if (s[i] == ')'){
            for (int j = 0; j <= n; j++){
                dp[i + 1][j] = dp[i][j] + dp[i][j + 1];
                dp[i + 1][j] %= 2012;
            }
            bal--;
        }
        // if (bal < 0){
        //     cout << "0\n";
        // }
    }
    // for (int i = 0; i <= n; i++)
    //     for (int j = 0; j <= n; j++)
    //         cout << dp[i][j] << " \n"[j == n];
    if (bal != 0)
        cout << "0\n";
    else
        cout << dp[n][0] << '\n';
    return 0;
}
 
signed main() {
#ifndef LOCAL
    freopen("bbreeds.in", "r", stdin);
    freopen("bbreeds.out", "w", stdout);
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