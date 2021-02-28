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

string s;
const int MAXN = 1e5 + 7;
const int MOD = 1e9 + 7;
ll dp[2][MAXN];
ll cnt[2];
int solve() {
    if (!(cin >> n >> s))
        return 1;
    fill(dp[0], dp[1] + n + 1, 0);
    fill(dp[0], dp[1] + n + 1, 0);
    dp[0][0] = 1;
    dp[1][0] = 1;
    cnt[0] = 0;
    cnt[1] = 0;
    for (int i = 0; i < n; i++){
        dp[0][i + 1] = cnt[0];
        dp[1][i + 1] = cnt[1];
        if (s[i] == '1' && i > 0){
            dp[s[i - 1] - '0'][i + 1] += dp[(s[i - 1] - '0') ^ 1][i - 1];
            cnt[s[i - 1] - '0'] += dp[(s[i - 1] - '0') ^ 1][i - 1];
        }
        dp[0][i + 1] %= MOD;
        dp[1][i + 1] %= MOD;
        cnt[0] %= MOD;
        cnt[1] %= MOD;
//        cout << dp[0][i + 1] << ' ' << dp[1][i + 1] << '\n';
        //        for (int j = i; j >= 1; j--)
//            if (s[j] == '1') {
//                dp[s[j - 1] - '0'][i + 1] = (dp[s[j - 1] - '0'][i + 1] + dp[(s[j - 1] - '0') ^ 1][j - 1]) % MOD;
//            }
//        if (s[i] == '1')
//            dp[i + 1] = (dp[i + 1] + 1) % MOD;
    }
    cout << (dp[0][n] + dp[1][n]) % MOD << '\n';
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
