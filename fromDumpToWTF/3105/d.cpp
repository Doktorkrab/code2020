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
const int MAXN = 705;

bool can[MAXN][MAXN];
bool dp[2][MAXN][MAXN]; // 0 - left, 1 - right
int arr[MAXN];
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            can[i][j] = (gcd(arr[i], arr[j]) > 1);

    for (int i = 0; i < 2; i++)
        for (int j = 0; j <= n; j++)
            for (int k = 0; k <= n; k++)
                dp[i][j][k] = (k == j);

    for (int i = 1; i < n; i++)
        dp[0][i][i + 1] = can[i - 1][i];
    for (int i = 0; i + 1 < n; i++)
        dp[1][i][i + 1] = can[i][i + 1];

    for (int l = 2; l <= n; l++){
        for (int i = 0; i + l <= n; i++){
            for (int j = i; j < i + l; j++){
                if (i > 0)
                    dp[0][i][i + l] |= (can[i - 1][j] && dp[1][i][j] && dp[0][j + 1][i + l]);
                if (i + 1 < n)
                    dp[1][i][i + l] |= (can[j][i + l] && dp[1][i][j] && dp[0][j + 1][i + l]);
                if (dp[0][i][i + l] && dp[1][i][i + l])
                    break;
            }
        }
    }
    // for (int i = 0; i < n; i++)
    //     for (int j = 0; j < n; j++)
    //         cout << can[i][j] << " \n"[j + 1 == n];
    // cout << '\n';
    // for (int i = 0; i < n; i++)
    //     for (int j = i; j <= n; j++)
    //         cout << dp[0][i][j] << " \n"[j == n];
    // cout << '\n';
    // for (int i = 0; i < n; i++)
    //     for (int j = i; j <= n; j++)
    //         cout << dp[1][i][j] << " \n"[j == n];
    bool ans = 0;
    for (int i = 0; i < n; i++){
        ans |= (dp[1][0][i] && dp[0][i + 1][n]);
        // cout << "root: " << arr[i] << '\n';
        // cout << "can left " << dp[1][0][i] << '\n';
        // cout << "can right " << dp[0][i + 1][n] << '\n';
    }
    if (ans)
        cout << "YES\n";
    else
        cout << "NO\n";
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