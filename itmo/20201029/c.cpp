#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
const int INF = 100;
const int MAXLOG = 5;
const int MAXLOG_N = 2e5;
#else
const int INF = 1e9;
const int MAXLOG = 25;
const int MAXLOG_N = 5e5 + 7;
#endif
using ll = long long;
const pair<int, int> MAX = {INF, INF};

// -*-*-* All variables *-*-*-

vector<vector<pair<int, int>>> sparse; // [LOG][N]
vector<vector<int>> g;
vector<int> logs;
vector<int> id;
vector<pair<int, int>> euler;
int n, m;

// -*-*-* All functions *-*-*-

void init() {
    g.assign(n, {});
    logs.assign(MAXLOG_N + 1, 0);
    for (int i = 2; i <= MAXLOG_N; i++) {
        logs[i] = logs[i / 2] + 1;
    }
    id.assign(n, -1);
    euler.clear();
}

void precalc(int v, int d, int p = -1) {
    id[v] = euler.size();
    euler.push_back({d, v});
    for (int u : g[v]) {
        if (u == p)
            continue;
        precalc(u, d + 1, v);
        euler.push_back({d, v});
    }
}

void build() {
    // cerr << "build\n";
    sparse.assign(MAXLOG, vector<pair<int, int>>(euler.size(), MAX));
    sparse[0] = euler;
    for (int log = 1; log < MAXLOG; log++) {
        for (int i = 0; i + (1 << (log - 1)) < (int) (euler.size()); i++) {
            sparse[log][i] =
                    min(sparse[log - 1][i], sparse[log - 1][i + (1 << (log - 1))]);
        }
    }
}

int get_min(int l, int r) {
    if (l > r)
        swap(l, r);
    int len = r - l + 1;
    int power = logs[len];
    return min(sparse[power][l], sparse[power][r - (1 << power) + 1]).second;
}

int lca(int a, int b) { return get_min(id[a], id[b]); }

int up[MAXLOG_N];
int down[MAXLOG_N];
int pp[MAXLOG_N];
bool dir[MAXLOG_N];

void dfs(int v, int p) {
    pp[v] = p;
    for (int u : g[v]) {
        if (u == p)
            continue;
        dfs(u, v);
        up[v] += up[u];
        down[v] += down[u];
    }
    if (down[v] && up[v]) {
        cout << "NO\n";
        exit(0);
    }
    if (down[v])
        dir[v] = true;
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    init();
    for (int i = 1; i < n; i++) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    precalc(0, 0);
    // cerr << "kek";
    build();
    for (int i = 0; i < m; i++) {
        int s, f;
        cin >> s >> f;
        --s, --f;
        int l = lca(s, f);
        up[s]++;
        up[l]--;
        down[l]--;
        down[f]++;
    }
    dfs(0, 0);
    cout << "YES\n";
    for (int i = 1; i < n; i++) {
        if (dir[i])
            cout << pp[i] + 1 << ' ' << i + 1 << '\n';
        else
            cout << i + 1 << " " << pp[i] + 1 << '\n';
    }
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