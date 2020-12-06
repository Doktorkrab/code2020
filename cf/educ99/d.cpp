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

int n, x;
const int MAXN = 505;
const int INF = 1e9;
int arr[MAXN];
int dp[MAXN][MAXN][MAXN];
void relax(int& a, int b){
    a = min(a, b);
}

int solve() {
    if (!(cin >> n >> x))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    for (int i = 0; i <= n; i++)
        for (int j = 0; j < MAXN; j++)
            for (int k = 0; k < MAXN; k++)
                dp[i][j][k] = INF;
    dp[0][x][0] = 0;
    for (int i = 0; i < n; i++){
        for (int x = 0; x < MAXN; x++)
            for (int last = 0; last < MAXN; last++){
                if (dp[i][x][last] >= INF)
                    continue;
                if (last <= arr[i])
                    relax(dp[i + 1][x][arr[i]], dp[i][x][last]);
                if (last <= x && x < arr[i])
                    relax(dp[i + 1][arr[i]][x], dp[i][x][last] + 1);
            }
    }
    int ans = INF;
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++)
            relax(ans, dp[n][i][j]);
    if (ans < INF)
        cout << ans << '\n';
    else
        cout << "-1\n";
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
