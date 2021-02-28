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

int n, s, t;
int m;
const int MAXN = 1e3 + 7;
const ll INF = 1e15;
vector<pair<int, int>> g1[MAXN];
vector<pair<int, int>> g2[MAXN];
vector<pair<int, int>> g3[2 * MAXN];

ll dist1[MAXN], dist2[MAXN];
int used[2 * MAXN];

void dijkstra(ll *dist, vector<pair<int, int>> *g) {
    fill(dist, dist + n, INF);
    fill(used, used + n, 0);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    dist[t] = 0;
    q.emplace(0, t);
    while (!q.empty()) {
        auto[_, v] = q.top();
        q.pop();
        if (used[v])
            continue;
        used[v] = 1;
        for (auto[u, w] : g[v]) {
            if (dist[u] > dist[v] + w) {
                dist[u] = dist[v] + w;
                q.emplace(dist[u], u);
            }
        }
    }
}

bool check_cycle(int v) {
    used[v] = 1;
    for (auto[u, w] : g3[v])
        if (used[u] == 1 || (!used[u] && check_cycle(u)))
            return true;
    used[v] = 2;
    return false;
}

ll dp[2 * MAXN];

ll calc_dp(int v) {
    if (used[v])
        return dp[v];
    if (v == t || v == t + n)
        return 0;
    used[v] = true;
    dp[v] = 0;
    for (auto[u, w] : g3[v])
        dp[v] = max(calc_dp(u) + w, dp[v]);
    return dp[v];
}

int solve() {
    if (!(cin >> n >> s >> t >> m))
        return 1;
    --s, --t;
    for (int i = 0; i < n; i++)
        g2[i].clear(), g1[i].clear(), g3[i].clear();
    for (int i = 0; i < 2 * n; i++)
        g3[i].clear();
    for (int i = 0; i < m; i++) {
        int v, u, l;
        cin >> v >> u >> l;
        v--, u--;
        g1[v].emplace_back(u, l);
        g1[u].emplace_back(v, l);
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int v, u, l;
        cin >> v >> u >> l;
        v--, u--;
        g2[v].emplace_back(u, l);
        g2[u].emplace_back(v, l);
    }
    dijkstra(dist1, g1);
    dijkstra(dist2, g2);

    for (int i = 0; i < n; i++) {
        for (auto[u, w] : g1[i]) {
            if (dist1[i] > dist1[u])
                g3[i].emplace_back(u + n, w);
        }
    }
    for (int i = 0; i < n; i++) {
        for (auto[u, w] : g2[i]) {
            if (dist2[i] > dist2[u])
                g3[i + n].emplace_back(u, w);
        }
    }
    fill(used, used + 2 * n, 0);
    if (check_cycle(s)) {
        cout << "-1\n";
        return 0;
    }
    fill(used, used + 2 * n, 0);
    cout << calc_dp(s) << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
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
