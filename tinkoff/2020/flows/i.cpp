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
struct Edge {
    int v, u, c, f, cost;
};
const int MAXE = 5e3 + 7;
const int MAXV = 1e2 + 7;
const ll INF = 1e9 + 7;
Edge edges[2 * MAXE];
int edge_now = 0;
int vertices = 0;
vector<int> g[MAXV];

ll dist[MAXV];
int from[MAXV];
ll potential[MAXV];
bool used[MAXV];

int s, t;

void add_edge(int v, int u, int w, int cost) {
    edges[edge_now] = {v, u, w, 0, cost};
    g[v].push_back(edge_now++);
    edges[edge_now] = {u, v, 0, 0, -cost};
    g[u].push_back(edge_now++);
}

void ford_bellman() {
    fill(dist, dist + vertices, INF);
    fill(from, from + vertices, -1);
    dist[s] = 0;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < edge_now; j++) {
            const auto &e = edges[j];
            if (e.c - e.f > 0 && dist[e.u] > dist[e.v] + e.cost) {
                dist[e.u] = dist[e.v] + e.cost;
                from[e.u] = j;
            }
        }
    }
}

void dijkstra() {
    fill(dist, dist + vertices, INF);
    fill(from, from + vertices, -1);
    fill(used, used + vertices, 0);
    dist[s] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    q.push({0, s});
    while (!q.empty()) {
        auto[_, v] = q.top();
        q.pop();
        if (used[v])
            continue;
        used[v] = true;
        for (int i : g[v]) {
            const auto &e = edges[i];
            ll cost = e.cost - potential[e.u] + potential[v];
            if (e.c - e.f > 0 && dist[e.u] > dist[e.v] + cost) {
                dist[e.u] = dist[e.v] + cost;
                from[e.u] = i;
                q.emplace(dist[e.u], e.u);
            }
        }
    }
    for (int i = 0; i < vertices; i++)
        dist[i] = dist[i] - potential[0] + potential[i];
}

void upd_potential() {
    copy(dist, dist + vertices, potential);
}

ll min_cost_max_flow() {
    ll ans = 0;
    ford_bellman();
    upd_potential();
    while (true) {
        dijkstra();
        upd_potential();
        if (dist[t] >= INF)
            break;
        ll flow = INF;
        int now = t;
        while (from[now] != -1) {
            const auto &e = edges[from[now]];
            flow = min(flow, 1LL * (e.c - e.f));
            now = e.v;
        }
        now = t;
        while (from[now] != -1) {
            ans += 1LL * flow * edges[from[now]].cost;
            edges[from[now]].f += flow;
            edges[from[now] ^ 1].f -= flow;
            now = edges[from[now]].v;
        }
    }
    return ans;
}


int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++)
        g[i].clear();
    s = 0, t = n - 1;
    vertices = n;
    for (int i = 0; i < m; i++) {
        int v, u, w, c;
        cin >> v >> u >> w >> c;
        add_edge(v - 1, u - 1, w, c);
    }
    cout << min_cost_max_flow() << '\n';
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
