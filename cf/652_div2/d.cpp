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
const int MAXN = 2e6 + 7;
const int MOD = 1e9 + 7;
int dp[MAXN];
 
int solve() {
    if (!(cin >> n))
        return 1;
    cout << dp[n] << '\n';
    return 0;
}
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
   cin >> tests;

    for (int i = 3; i <= MAXN; i++){
        dp[i] = (((dp[i - 2] * 2LL) % MOD) + dp[i - 1]) % MOD + (i % 3 == 0) * 4;
        dp[i] %= MOD;
    }
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}