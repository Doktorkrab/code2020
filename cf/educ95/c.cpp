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
const int MAXN = 2e5 + 7;
const int INF = 1e9;
int dp[2][3][MAXN];
int arr[MAXN]; 
int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    dp[0][1][n - 1] = 0;
    dp[1][1][n - 1] = arr[n - 1];
    dp[0][2][n - 1] = INF;
    dp[1][2][n - 1] = INF;
    for (int i = n - 2; i >= 0; i--){
        dp[0][1][i] = min(dp[1][1][i + 1], dp[1][2][i + 1]);
        dp[0][2][i] = dp[0][1][i + 1];
        dp[1][1][i] = min(dp[0][1][i + 1], dp[0][2][i + 1]) + arr[i];
        dp[1][2][i] = dp[1][1][i + 1] + arr[i];
    }
    cout << min(dp[1][1][0], dp[1][2][0]) << '\n';
    return 0;
}
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}
