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
 
int n, k;
const int MAXN = 50;
int dp[MAXN][MAXN];
int arr[MAXN];
int solve() {
    if (!(cin >> n >> k))
        return 1;
    for (int i = 0; i <= k; i++)
        for (int j = 0; j <= n; j++)
            dp[i][j] = 0;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    for (int i = 1; i <= k; i++)
        for (int j = 0; j < n; j++){
            int have = 0;
            for (int x = j; x >= 0; x--){
                have |= arr[x];
                dp[i][j + 1] = max(dp[i][j + 1], dp[i - 1][x] + have);
            }
        }
    cout << dp[k][n] << '\n';
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
