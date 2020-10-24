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
const int MAXN = 2005;
const ll INF = TMAX(ll) / 2;
ll dp[MAXN][MAXN];
ll cost[MAXN][MAXN];
int opt[MAXN][MAXN];
ll arr[MAXN];

string ans[MAXN];

void dfs(int l, int r, string &have) {
    ans[opt[l][r]] = have;
    if (r - l == 1)
        return;
    have += '0';
    dfs(l, opt[l][r], have);
    have.pop_back();
    have += '1';
    dfs(opt[l][r], r, have);
    have.pop_back();
}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    for (int i = 0; i < n; i++) {
        dp[i][i + 1] = 0;
        opt[i][i + 1] = i;
        ll now = 0;
        for (int j = i; j <= n; j++) {
            cost[i][j] = now;
            if (j < n)
                now += arr[j];
        }
    }
    for (int l = 2; l <= n; l++)
        for (int i = 0; i + l <= n; i++) {
            dp[i][i + l] = INF;
            for (int k = opt[i][i + l - 1]; k <= opt[i + 1][i + l]; k++) {
                ll now = min(INF, dp[i][k] + dp[k][i + l]);
                if (now < dp[i][i + l]) {
                    dp[i][i + l] = now;
                    opt[i][i + l] = k;
                }
            }
            dp[i][i + l] += cost[i][i + l];
        }
    string have;
    dfs(0, n, have);
    for (int i = 0; i < n; i++)
        cout << ans[i] << '\n';
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
