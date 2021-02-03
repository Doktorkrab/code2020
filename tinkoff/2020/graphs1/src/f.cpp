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

int n, m, r;
const int MAXN = 5e5 + 7;
const int MAXLOG = 19;
vector<pair<int, int>> g[MAXN]; // (u, index)
int fup[MAXN];
int tin[MAXN];
int tout[MAXN];
int timer = 0;
bool is_bridge[MAXN];
pair<int, int> edges[MAXN];
bool used[MAXN];
set<int> g1[MAXN];
int color[MAXN];
int depth[MAXN];
int p[MAXLOG][MAXN];

int dfs(int v, int p = -1) {
    used[v] = true;
    tin[v] = fup[v] = timer++;
    for (auto[u, index] : g[v]) {
        if (u == p)
            continue;
        if (used[u]) {
            fup[v] = min(fup[v], tin[u]);
        } else {
            fup[v] = min(fup[v], dfs(u, v));
            if (tin[v] < fup[u])
                is_bridge[index] = true;
        }
    }
    return fup[v];
}

void paint(int v, int c) {
    color[v] = c;
    for (auto[u, index] : g[v])
        if (color[u] == -1 && !is_bridge[index])
            paint(u, c);
}


void calc_depth(int v, int par, int d) {
    depth[v] = d;
    p[0][v] = par;
    tin[v] = timer++;
    for (int i = 1; i < MAXLOG; i++)
        p[i][v] = p[i - 1][p[i - 1][v]];
    for (int u : g1[v])
        if (u != par)
            calc_depth(u, v, d + 1);
    tout[v] = timer++;
}

inline bool is_anc(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
    if (is_anc(a, b))
        return a;
    for (int i = MAXLOG - 1; i >= 0; i--) {
        int v = p[i][a];
        if (!is_anc(v, b))
            a = v;
    }
    return p[0][a];
}

int solve() {
    if (!(cin >> n >> m >> r))
        return 1;
    --r;
    for (int i = 0; i < n; i++) {
        g[i].clear();
        g1[i].clear();
    }
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].emplace_back(u, i);
        g[u].emplace_back(v, i);
        edges[i] = {v, u};
    }
    timer = 0;
    fill(used, used + n, false);
    fill(is_bridge, is_bridge + n, false);
    for (int i = 0; i < n; i++)
        if (!used[i])
            dfs(i, -1);
    int c = 0;
    fill(color, color + n, -1);
    for (int i = 0; i < n; i++)
        if (color[i] == -1)
            paint(i, c++);

    for (int i = 0; i < n; i++) {
        for (auto[u, _] : g[i])
            if (color[i] != color[u]) {
                g1[color[i]].insert(color[u]);
                g1[color[u]].insert(color[i]);
            }
    }
    r = color[r];
    fill(tin, tin, 0);
    timer = 0;
    calc_depth(r, r, 0);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        cout << depth[lca(color[a - 1], color[b - 1])] << '\n';
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("f.in", "r", stdin);
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
