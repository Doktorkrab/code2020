#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
const int INF = 1e9;
#else
const int INF = 1e9;
#endif

// -*-*-* All variables *-*-*-
vector<vector<int>> dp;
int n, k;
// -*-*-* All functions *-*-*-
void init() {}
void solve() {
    init();
    cin >> n >> k;
    dp.assign(n + 1, vector<int>(k + 1, INF));
    for (int i = 0; i <= k; i++)
        dp[0][i] = 0;
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= n; j++) {
            for (int g = 1; g <= j; g++) {
                dp[j][i] = min(dp[j][i], max(dp[j - g][i - 1], dp[g - 1][i - 1] + 1));
            }
        }
    }
    cout << setw(5);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= k; j++)
            if (dp[i][j] == INF)
                cout << setw(3) << "INF" << " \n"[j == k];
            else
                cout << setw(3) << dp[i][j] << " \n"[j == k];
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}