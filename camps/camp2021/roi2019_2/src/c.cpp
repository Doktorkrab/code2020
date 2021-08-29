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

int n, m, k;
const int MAXN = 1e3 + 7;
const int MOD = 998244353;
int dp[2][MAXN][MAXN];
bool was[MAXN][MAXN];

int mod(int a) {
    return (a % MOD + MOD) % MOD;
}

int add(int a, int b) {
    return (a + MOD + b) % MOD;
}

int mul(int a, int b) {
    return (a * b) % MOD;
}

int solve() {
    if (!(cin >> n >> m >> k))
        return 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            dp[0][i][j] = dp[1][i][j] = was[i][j] = false;
        }
    for (int i = 0; i < k; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        --x, --y;
        dp[0][x][y] = dp[1][x][y] = w;
        was[x][y] = true;
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            if (was[i][j])
                continue;
            dp[0][i][j] = TMAX(int);
            dp[1][i][j] = TMIN(int);
            if (i + 1 < n) {
                dp[0][i][j] = dp[1][i + 1][j];
                dp[1][i][j] = dp[0][i + 1][j];
            }
            else
                dp[0][i][j] = dp[1][i][j] = 0;
            if (j + 1 < m) {
                dp[0][i][j] = min(dp[0][i][j], dp[1][i][j + 1]);
                dp[1][i][j] = max(dp[1][i][j], dp[0][i][j + 1]);
            }
            else {

                dp[0][i][j] = min(dp[0][i][j], 0LL);
                dp[1][i][j] = max(dp[1][i][j], 0LL);
            }
        }
    }
//    for (int i = 0; i < n; i++)
//        for (int j = 0; j < m; j++)
//            cout << dp[0][i][j] << " \n"[j + 1 == m];
//    cout << '\n';
//    for (int i = 0; i < n; i++)
//        for (int j = 0; j < m; j++)
//            cout << dp[1][i][j] << " \n"[j + 1 == m];
    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            ans = add(ans, mod(dp[0][i][j]));
    cout << ans << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
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
