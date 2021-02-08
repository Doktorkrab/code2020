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

int n, m;
const int MAXN = 4e5 + 7;
int tin[MAXN];
int fup[MAXN];
int timer = 0;
vector<int> g[MAXN];
bool is_good[MAXN], used[MAXN];

inline void add_edge(int a, int b) {
    g[a].push_back(b);
    g[b].push_back(a);
}

int dfs(int v, int p = -1) {
    tin[v] = fup[v] = timer++;
    used[v] = true;
    int cnt = 0;
    for (int u : g[v]) {
        if (u == p)
            continue;
        if (used[u]) {
            fup[v] = min(fup[v], tin[u]);
        } else {
            cnt++;
            fup[v] = min(fup[v], dfs(u, v));
            if (fup[u] >= tin[v] && p != -1)
                is_good[v] = true;
        }
    }
    if (p == -1 && cnt > 1)
        is_good[v] = true;
    return fup[v];
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n + m; i++)
        g[i].clear();
    for (int i = 0; i < m; i++) {
        int v, u, w;
        cin >> v >> u >> w;
        --v, --u, --w;
        add_edge(v, n + i);
        add_edge(u, n + i);
        add_edge(w, n + i);
    }
    fill(is_good, is_good + n + m, false);
    fill(used, used + n + m, false);
    for (int i = 0; i < n + m; i++)
        if (!used[i])
            dfs(i, -1);
    int ans = count(is_good + n, is_good + n + m, true);
    cout << ans << '\n';
    for (int i = 0; i < m; i++)
        if (is_good[i + n])
            cout << i + 1 << " ";
    cout << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("q.in", "r", stdin);
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
