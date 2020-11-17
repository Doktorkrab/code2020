#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <ctime>
#include <bitset>
#include <complex>

#define FAST_ALLOCATOR_MEMORY 2e8
// #ifdef FAST_ALLOCATOR_MEMORY
//     int allocator_pos = 0;
//     char allocator_memory[(int)FAST_ALLOCATOR_MEMORY];
//     inline void * operator new ( size_t n ) {
//         char *res = allocator_memory + allocator_pos;
//         allocator_pos += n;
//         assert(allocator_pos <= (int)FAST_ALLOCATOR_MEMORY);
//         return (void *)res;
//     }
//     inline void operator delete ( void * ) noexcept { }
//     //inline void * operator new [] ( size_t ) { assert(0); }
//     //inline void operator delete [] ( void * ) { assert(0); }
// #endif
// #define int long long
#define SZ(x) (int)((x).size())
#define ALL(x) (x).begin(), (x).end()
using namespace std;
const int INF = 1e9;
struct Edge {
    int v, u, c, f, cost;
};
struct Segment {
    int l, r, c;
};
vector<Edge> edges;
vector<vector<int>> g;
vector<int> dist;
vector<int> p;
vector<int> from;
vector<bool> used;
vector<Segment> segments;
int n, k, s, t;

void ford_bellman() {
    fill(ALL(dist), INF);
    fill(ALL(from), -1);
    // fill(ALL(used), 0);
    dist[s] = 0;
    for (int i = 0; i <= SZ(dist); i++) {
        bool relaxed = 0;
        for (int j = 0; j < SZ(edges); j++) {
            const Edge &e = edges[j];
            if (e.c - e.f > 0 && dist[e.v] + e.cost < dist[e.u]) {
                relaxed = 1;
                dist[e.u] = dist[e.v] + e.cost;
                from[e.u] = j;
            }
        }
        if (!relaxed)
            return;
    }
}

void dijkstra() {
    fill(ALL(used), 0);
    fill(ALL(dist), INF);
    fill(ALL(from), -1);
    dist[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({0, s});
    while (!q.empty()) {
        auto[_, v] = q.top();
        q.pop();
        if (used[v])
            continue;
        used[v] = 1;
        for (int u : g[v]) {
            const auto &e = edges[u];
            int cost = e.cost + p[e.v] - p[e.u];
            if (e.c - e.f > 0 && dist[v] + cost < dist[e.u]) {
                dist[e.u] = dist[v] + cost;
                from[e.u] = u;
                q.push({dist[e.u], e.u});
            }
        }
    }
    for (int i = 0; i < SZ(dist); i++)
        dist[i] = dist[i] - p[0] + p[i];
}

void recalc_p() {
    for (int i = 0; i < SZ(dist); i++)
        p[i] = dist[i];
}

inline void init() {
    used.resize(2 * n + 3);
    dist.resize(2 * n + 3);
    from.resize(2 * n + 3);
    g.resize(2 * n + 3);
    p.resize(2 * n + 3);
    segments.resize(n);
}

inline bool is_inter(const Segment &a, const Segment &b) {
    return max(a.l, b.l) < min(a.r, b.r);
}

void add_edge(int v, int u, int c, int cost) {
    g[v].push_back(SZ(edges));
    edges.push_back({v, u, c, 0, cost});
    g[u].push_back(SZ(edges));
    edges.push_back({u, v, 0, 0, -cost});
}

inline void solve() {
    init();
    for (int i = 0; i < n; i++) {
        int s, t, c;
        cin >> s >> t >> c;
        segments[i] = {s, s + t, c};
    }
    s = 0;
    t = 2;
    add_edge(1, 2, k, 0);
    for (int i = 0; i < n; i++)
        add_edge(s, i + 3, 1, 0);
    for (int i = 0; i < n; i++)
        add_edge(i + n + 3, 1, 1, 0);
    for (int i = 0; i < n; i++)
        add_edge(i + 3, i + n + 3, 1, -segments[i].c);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (is_inter(segments[i], segments[j]))
                continue;
            int a = i;
            int b = j;
            if (segments[i].l > segments[j].l)
                swap(a, b);
            add_edge(a + n + 3, b + 3, 1, 0);
        }
    }
    ford_bellman();
    recalc_p();
    int ans1 = 0;
    while (1) {
        dijkstra();
        recalc_p();
        if (!used[t])
            break;
        int nxt = INF;
        int now = t;
        while (from[now] != -1) {
            auto e = edges[from[now]];
            // cerr << '\t' << e.c - e.f << '\n';
            nxt = min(nxt, e.c - e.f);
            now = e.v;
        }
        // cerr << nxt << '\n';
        assert(nxt != 0);
        now = t;
        while (from[now] != -1) {
            // cerr << edges[from[now]].v << ' ' << edges[from[now]].u << '\n';
            ans1 += -edges[from[now]].cost * nxt;
            edges[from[now]].f += nxt;
            edges[from[now] ^ 1].f -= nxt;
            now = edges[from[now]].v;
        }
    }
    vector<int> ans(n);
    for (const auto &e : edges) {
        if (0 <= e.v - 3 && e.v - 3 < n && 0 <= e.u - 3 - n && e.u - 3 - n < n && e.u - e.v == n) {
            ans[e.v - 3] = e.f;
        }
    }
    for (int i : ans)
        cout << i << ' ';
    cout << '\n';
}


int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    while (cin >> n >> k)
        solve();
}
