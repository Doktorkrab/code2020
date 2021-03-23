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
//#define int ll
const int MAXN = 2e3 + 7;
const ll INF = 1e18;
int opt[MAXN][MAXN];
ll dp[MAXN][MAXN];
ll cost[MAXN][MAXN];
int arr[MAXN];
string ans[MAXN];

void dfs(int l, int r, string &have) {
//    cout << l << ' ' << r << '\n';
    ans[opt[l][r]] = have;
    if (r - l == 1)
        return;
    have += '0';
    dfs(l, opt[l][r], have);
    have.back() = '1';
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
        for (int j = i; j < n; j++) {
            now += arr[j];
            cost[i][j + 1] = now;
        }
    }
    for (int l = 2; l <= n; l++) {
        for (int i = 0; i + l <= n; i++) {
            dp[i][i + l] = INF;
            for (int j = opt[i][i + l - 1]; j <= opt[i + 1][i + l]; j++) {
                ll now = min(INF, dp[i][j] + dp[j][i + l]);
                if (now < dp[i][i + l]) {
                    dp[i][i + l] = now;
                    opt[i][i + l] = j;
                }
            }
            dp[i][i + l] += cost[i][i + l];
        }
    }
    string a;
    dfs(0, n, a);
    for (int i = 0; i < n; i++)
        cout << ans[i] << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("e.in", "r", stdin);
#else
    freopen("codes.in", "r", stdin);
    freopen("codes.out", "w", stdout);
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
