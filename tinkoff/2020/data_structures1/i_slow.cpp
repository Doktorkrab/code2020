#include <bits/stdc++.h>

using namespace std;
const int MAXN = 1005;
int dp[2][MAXN][MAXN];
int ans[MAXN];

int main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int &i : a)
        cin >> i;
    for (int &i : b)
        cin >> i;
    for (int i = 0; i < n; i++) {
        dp[0][1][i] = a[i];
        dp[1][1][i] = b[i];
        for (int j = 2; j <= n && i > 0; j++) {
            dp[0][j][i] = max(dp[0][j][i - 1], min(dp[0][j - 1][i - 1], a[i]));
            dp[1][j][i] = max(dp[1][j][i - 1], min(max(dp[0][j - 1][i - 1], dp[1][j - 1][i - 1]), b[i]));
        }
        for (int j = 1; j <= n; j++)
            ans[j] = max(ans[j], max(dp[0][j][i], dp[1][j][i]));
    }
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " \n"[i == n];
}
