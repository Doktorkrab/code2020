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
const int MAXN = 20;
vector<int> g[MAXN];
vector<vector<vector<int>>> dp(MAXN, vector<vector<int>>(MAXN, vector<int>(2)));

char rec(int mask, int v, int u, int turn) {
    if (dp[v][u][turn] != -1)
        return dp[v][u][turn];
    if (turn == 0) {
        for (int k : g[v])
            if (!((mask >> k) & 1)) {
                if (!rec(mask | (1 << k), k, u, 1 - turn))
                    return dp[v][u][turn] = 1;
            }
        return dp[v][u][turn] = 0;
    }
    for (int k : g[u])
        if (!((mask >> k) & 1)) {
            if (!rec(mask | (1 << k), v, k, 1 - turn))
                return dp[v][u][turn] = 1;
        }
    return dp[v][u][turn] = 0;


}

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        g[i].clear();
    for (int i = 0; i + 1 < n; i++) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                dp[j][k][0] = dp[j][k][1] = -1;
    for (int i = 0; i < n; i++) {
        bool good = true;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                for (int w = 0; w < n; w++)
                    for (int k = 0; k < n; k++)
                        dp[w][k][0] = dp[w][k][1] = -1;
                good &= rec((1 << i) | (1 << j), i, j, 0);
            }
//            if (i == 1)
//                cout << j << ' ' << good << '\n';
        }
        if (good) {
//            cout << i << '\n';
            cout << "Yes\n";
            return 0;
        }
    }
    cout << "No\n";
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("winner.in", "r", stdin);
#endif
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
