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

int subtask;
int nx, mx, ny, my;
enum DIRECTION {
    X, Y
};

struct Edge {
    int type;
    int v, u;
    ll w;

    bool operator<(const Edge &rhs) const;
};

bool Edge::operator<(const Edge &rhs) const {
    return std::tie(w, type, v, u) < std::tie(rhs.w, rhs.type, rhs.v, rhs.u);
}

const int MAXN = 5e4 + 5;
const ll INF = 1e18;
Edge edges[2 * MAXN];
vector<pair<int, ll>> g_x[MAXN];
vector<pair<int, ll>> g_y[MAXN];

ll dist[MAXN];
bool used[MAXN];

ll dijkstra(vector<pair<int, ll>> *g, int n) {
    fill(dist, dist + n, INF);
    fill(used, used + n, false);
    dist[0] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.emplace(0, 0);
    while (!q.empty()) {
        auto[a, v] = q.top();
        q.pop();
        if (used[v])
            continue;
        used[v] = true;
        for (auto[u, w] : g[v]) {
            ll nxt = dist[v] + w;
            if (dist[u] > nxt) {
                dist[u] = nxt;
                q.emplace(dist[u], u);
            }
        }
    }
    return dist[n - 1];
}

void solve_1() {
    cin >> nx >> mx;
    for (int i = 0; i < nx; i++)
        g_x[i].clear();
    for (int i = 0; i < mx; i++) {
        int v, u, w;
        cin >> v >> u >> w;
        --v, --u;
        g_x[v].emplace_back(u, w);
        g_x[u].emplace_back(v, w);
    }
    cin >> ny >> my;
    for (int i = 0; i < ny; i++)
        g_y[i].clear();
    for (int i = 0; i < my; i++) {
        int v, u, w;
        cin >> v >> u >> w;
        --v, --u;
        g_y[v].emplace_back(u, w);
        g_y[u].emplace_back(v, w);
    }
    cout << dijkstra(g_x, nx) + dijkstra(g_y, ny) << '\n';
}

int px[MAXN], py[MAXN];
int szx[MAXN], szy[MAXN];
int cntx, cnty;

int find_set(int *p, int v) {
    if (p[v] == v)
        return v;
    return p[v] = find_set(p, p[v]);
}

bool un(int *p, int *sz, int v, int u) {
    v = find_set(p, v);
    u = find_set(p, u);
    if (v == u)
        return false;
    if (sz[v] > sz[u])
        swap(v, u);
    p[v] = u;
    sz[u] += sz[v];
    return true;
}

void solve_2() {
    cin >> nx >> mx;
    iota(px, px + nx, 0);
    fill(szx, szx + nx, 1);
    cntx = nx;
    for (int i = 0; i < mx; i++) {
        int v, u, w;
        cin >> v >> u >> w;
        --v, --u;
        edges[i] = {X, v, u, w};
    }
    cin >> ny >> my;
    iota(py, py + ny, 0);
    fill(szy, szy + ny, 1);
    cnty = ny;
    for (int i = 0; i < my; i++) {
        int v, u, w;
        cin >> v >> u >> w;
        --v, --u;
        edges[i + mx] = {Y, v, u, w};
    }
    sort(edges, edges + mx + my);
    ll ans = 0;
    for (int i = 0; i < mx + my; i++) {
        int v = edges[i].v;
        int u = edges[i].u;
        ll w = edges[i].w;
        if (edges[i].type == X) {
            if (un(px, szx, v, u))
                ans += w * cnty, cntx--;
        }
        if (edges[i].type == Y) {
            if (un(py, szy, v, u))
                ans += w * cntx, cnty--;
        }
    }
    cout << ans << '\n';
}

int solve() {
    if (!(cin >> subtask))
        return 1;
    if (subtask == 1)
        solve_1();
    else
        solve_2();
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
