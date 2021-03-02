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
const int MAXN = 2e5 + 7;
const ll INF = 1e18;
vector<pair<int, int>> g[MAXN], g1[MAXN];
int a, b;
int s, t;
ll dist_s[MAXN];
ll dist_t[MAXN];
ll dist_a[MAXN];
ll dist_b[MAXN];
ll dp[MAXN];
bool used[MAXN];

void dijkstra(int start, ll *dist) {
    fill(dist, dist + n, INF);
    fill(used, used + n, false);
    dist[start] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    q.emplace(0, start);
    while (SZ(q)) {
        auto[d, v] = q.top();
        q.pop();
        if (used[v])
            continue;
//        cout << start + 1 << ' ' << v + 1 << '\n';
        used[v] = true;
        for (auto[u, w] : g[v]) {
            if (dist[u] > dist[v] + w) {
                dist[u] = dist[v] + w;
                q.emplace(dist[u], u);
            }
        }
    }
}

ll calc_dp(int v, ll *dists) {
    if (v == t)
        return dp[v] = dists[v];
    if (dp[v] != -1)
        return dp[v];
    dp[v] = dists[v];
    for (auto[u, w] : g1[v])
        dp[v] = min(calc_dp(u, dists), dp[v]);
    return dp[v];
}

ll find_ans(int a, int b) {
    fill(dp, dp + n, -1);
    dijkstra(a, dist_a);
    dijkstra(b, dist_b);
//    for (int i = 0; i < n; i++)
//        cout << dist_a[i] << " \n"[i + 1 == n];
//    for (int i = 0; i < n; i++)
//        cout << dist_b[i] << " \n"[i + 1 == n];
    ll best = INF;
    for (int i = 0; i < n; i++) {
//        cout << i + 1 << ' ' << calc_dp(i, dist_b) << ' ' << dist_a[i] << "\n";
        best = min(best, calc_dp(i, dist_b) + dist_a[i]);
    }
//    cout << '\n';
    return best;
}

int solve() {
    if (!(cin >> n >> m >> s >> t >> a >> b))
        return 1;
    --s, --t;
    --a, --b;
    for (int i = 0; i < n; i++)
        g[i].clear(), g1[i].clear();
    for (int i = 0; i < m; i++) {
        int v, u, w;
        cin >> v >> u >> w;
        --v, --u;
        g[v].emplace_back(u, w);
        g[u].emplace_back(v, w);
    }
    dijkstra(s, dist_s);
    dijkstra(t, dist_t);
    for (int v = 0; v < n; v++)
        for (auto[u, w] : g[v])
            if (dist_s[v] + w + dist_t[u] == dist_s[t]) {
//                cout << v + 1 << ' ' << u + 1 << ' ' << dist_s[v] << ' ' << w << ' ' << dist_t[u] << '\n';
                g1[v].emplace_back(u, w);
            }
//    for (int i = 0; i < n; i++)
//        for (auto [u, w] : g1[i])
//            cout << i + 1 << " " << u + 1 << '\n';
    cout << min(find_ans(a, b), find_ans(b, a)) << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
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
