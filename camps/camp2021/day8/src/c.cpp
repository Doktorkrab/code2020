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

int n, q;
const int MAXN = 5e5 + 7;
bool can[MAXN];
int cnt_bad[MAXN];
bool used[MAXN];
int dp[MAXN];
bool banned[MAXN];
int sz[MAXN];
int cnt[MAXN];
vector<int> g[MAXN];

void dfs_stupid(int v, int p) {
    used[v] = true;
    int where = -1;
    dp[v] = 0;
    for (int u : g[v]) {
        if (u == p || banned[u])
            continue;
        dfs_stupid(u, v);
        if (dp[u] == 1)
            continue;
        if (dp[u] == 0 || where != -1)
            return;
        where = u;
    }
    if (where == -1)
        dp[v] = 2;
    else
        dp[v] = 1;
}

void dfs(int v, int p) {
    sz[v] = 1;
    cnt[v] = 0;
    for (int u : g[v]) {
        if (u == p)
            continue;
        dfs(u, v);
        sz[v] += sz[u];
        cnt[v] += (sz[u] % 2);
    }
}

void dfs1(int v, int p) {
    if (p == -1)
        can[v] = true;
    else {
        can[v] = can[p];
        cnt_bad[v] = cnt_bad[p];
        if (sz[v] % 2)
            can[v] &= (cnt[p] <= 2), cnt_bad[v] += (cnt[p] == 2);
        else
            can[v] &= (cnt[p] == 0);
    }
    for (int u : g[v]) {
        if (u == p)
            continue;
        dfs1(u, v);
    }
}

int solve() {
    if (!(cin >> n >> q))
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
    fill(used, used + n, false);
    dfs(0, -1);
    int was2 = 0;
    for (int i = 0; i < n; i++)
        if (cnt[i] >= 2)
            was2++;
    dfs1(0, -1);

    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        if (n <= 3000) {
            vector<int> x(k);
            for (int &y : x) {
                cin >> y;
                --y;
                banned[y] = true;
            }
            fill(used, used + n, false);
            bool good = false;
            for (int j = 0; j < n; j++) {
                if (used[j] || banned[j])
                    continue;
                dfs_stupid(j, -1);
                good |= (dp[j] != 1);
            }
            for (int y : x)
                banned[y] = false;
            cout << !good << " \n"[i + 1 == q];
            continue;
        }
//        continue;
        int v;
        cin >> v;
        --v;
        if (v == 0) {
            cout << (cnt[0] == 0 && !was2) << " \n"[i + 1 == q];
            continue;
        }
        if (cnt[v] != 0) {
            cout << 0 << " \n"[i + 1 == q];
            continue;
        }
        cout << (can[v] && (was2 - cnt_bad[v] == 0)) << " \n"[i + 1 == q];


    }

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
