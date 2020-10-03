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
string s, t;
const int MAXN = 1200;
int dp[MAXN][MAXN];
int lazy_dp(int i, int j){
    if (i == n && j == m)
        return 0;
    if (i == n)
        return 1e9 + 7;
    if (j == m)
        return lazy_dp(i + 1, j) + 1;
    if (dp[i][j] != -1)
        return dp[i][j];
    return dp[i][j] = min(lazy_dp(i + 1, j + 1) + (s[i] != t[j]), lazy_dp(i + 1, j) + 1);
}
int solve() {
    if (!(cin >> s >> t))
        return 1;
    n = SZ(s);
    m = SZ(t);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            dp[i][j] = -1;
    cout << lazy_dp(0, 0) << '\n';
    //for (int i = 0; i < n; i++)
        //for (int j = 0; j < m; j++)
            //cout << lazy_dp(i, j) << " \n"[j + 1 == m];
    return 0;
}
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
        freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
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
