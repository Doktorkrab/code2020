//#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;
#define int ll

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

int n, m;
const int MAXN = 2e5 + 7;
const int MAXLOG = 18;
vector<vector<int>> g(MAXN);
//vector<int> g[MAXN];
vector<vector<int>> parents(MAXLOG, vector<int>(MAXN));
//int parents[MAXLOG][MAXN];
vector<int> start(MAXN);
//int start[MAXN];
vector<int> sz(MAXN);
vector<int> pos(MAXN);
vector<int> way(MAXN);
vector<int> dp(MAXN);
vector<int> depth(MAXN);
vector<int> logs(MAXN);
//int sz[MAXN];
//int pos[MAXN];
//int way[MAXN];
//int dp[MAXN];
//int depth[MAXN];
//int logs[MAXN];
//vector<int> paths[MAXN];
vector<vector<int>> paths(MAXN);

void dfs(int v, int p, int d) {
    parents[0][v] = p;
    dp[v] = d;
    depth[v] = d;
    for (int i = 1; i < MAXLOG; i++)
        parents[i][v] = parents[i - 1][parents[i - 1][v]];
    for (int u : g[v])
        if (u != p) {
            dfs(u, v, d + 1);
            dp[v] = max(dp[v], dp[u]);
        }
    if (SZ(g[v]) > 1) {
        int index = -1;
        for (int j = 0; j < SZ(g[v]); j++) {
            if (g[v][j] != p && (index == -1 || dp[g[v][index]] < dp[g[v][j]]))
                index = j;
        }
        assert(dp[v] == dp[g[v][index]]);
        swap(g[v][0], g[v][index]);
    }
}

int now = 0;

void build_paths(int v, int p, int path = -1) {
    if (path == -1) {
        start[now] = v;
        path = now++;
    }
    way[v] = path;
    paths[path].push_back(v);
    int nxt = path;
    for (int u : g[v]) {
        if (u == p)
            continue;
        build_paths(u, v, nxt);
        nxt = -1;
    }
}

int get_ancestor(int v, int k) {
    if (k == 0)
        return v;
    int d = k;
//    d -= k;
    if (d < 0)
        d = 0;
    int x = logs[d];
    v = parents[x][v];
    x = max(0LL, d - (1LL << x));
//    assert(pos[v] - x >= 0);
    return paths[way[v]][max(0LL, pos[v] - x)];
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 1; i < n; i++) {
        int x;
        cin >> x;
        g[i].push_back(x);
        g[x].push_back(i);
    }
    dfs(0, 0, 0);
    build_paths(0, 0, -1);
    for (int i = 0; i < now; i++) {
        reverse(ALL(paths[i]));
        int cnt = SZ(paths[i]);
        for (int j = 0; j < cnt; j++) {
            paths[i].push_back(parents[0][start[i]]);
            start[i] = parents[0][start[i]];
        }
        reverse(ALL(paths[i]));
        for (int j = cnt; j < SZ(paths[i]); j++)
            pos[paths[i][j]] = j;
    }
    int a1, a2;
    int x, y, z;
    cin >> a1 >> a2 >> x >> y >> z;
    ll sum = 0;
    int last = 0;
    for (int i = 0; i < m; i++) {
        int t = get_ancestor((a1 + last) % n, a2);
        sum += t;
//        cout << (a1 + last) % n << ' ' << a2 << ' ' << t << '\n';
        a1 = (1LL * x * a1 + y * a2 + z) % n;
        a2 = (1LL * x * a2 + y * a1 + z) % n;
        last = t;
    }
    cout << sum << '\n';
    return 0;
}

void precalc() {
    logs[0] = 0;
    for (int i = 2; i < MAXN; i++)
        logs[i] = logs[i / 2] + 1;
}

signed main() {
    precalc();
#ifdef LOCAL
    freopen("m.in", "r", stdin);
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
