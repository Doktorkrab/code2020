//#pragma GCC optimize("O3")
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

namespace pre_flow {
    const int MAXV = 500;
    const int MAXE = 1e4;

    struct Edge {
        int v, u;
        ll c, f;
        int nxt = -1;

        Edge() = default;

        Edge(int v, int u, ll c, ll f, int nxt) : v(v), u(u), c(c), f(f), nxt(nxt) {}
    };

    Edge edges[2 * MAXE];
    int pnt = 0;
    int head[MAXV];
    int cur[MAXV];
    int d[MAXV];
    ll exc[MAXV];
    bool used[MAXV];
    queue<int> have;
    int s, t;
    int n, m;
    ll ans = 0;

    inline void push(int e_id, bool is_start = false) {
        auto &e = edges[e_id];
        if (e.c - e.f <= 0)
            return;
        if (!is_start && d[e.v] != d[e.u] + 1)
            return;
        ll flow = e.c - e.f;
        if (e.v != s)
            flow = min(flow, exc[e.v]);
        if (e.u != t)
            exc[e.u] += flow;
        else
            ans += flow;
        if (e.v != s)
            exc[e.v] -= flow;

        if (exc[e.v] > 0 && !used[e.v]) {
            used[e.v] = true;
            have.push(e.v);
        }
        if (exc[e.u] > 0 && !used[e.u]) {
            used[e.u] = true;
            have.push(e.u);
        }

        e.f += flow;
        edges[e_id ^ 1].f -= flow;
    }

    inline void relabel(int v) {
        int mn = TMAX(int);
        for (int i = head[v]; i != -1; i = edges[i].nxt)
            if (edges[i].c - edges[i].f > 0)
                mn = min(mn, d[edges[i].u] + 1);
        if (v == s)
            d[v] = n;
        if (v == t)
            d[v] = 0;
        else
            d[v] = mn;
    }

    inline void discharge(int v) {
        for (int &i = cur[v]; i != -1; i = edges[i].nxt)
            push(i);
        if (exc[v] > 0) {
            relabel(v);
            cur[v] = head[v];
        }
    }

    inline void init() {
        n = ::n;
        m = ::m;
        fill(head, head + n, -1);
    }

    inline void add_edge(int v, int u, int w) {
        edges[pnt] = Edge(v, u, w, 0, head[v]);
        head[v] = pnt++;
        edges[pnt] = Edge(u, v, 0, 0, head[u]);
        head[u] = pnt++;
    }
    void global_relabel(int start){

    }
    ll max_flow() {
        d[t] = 0;
        d[s] = n;
        ans = 0;
        for (int i = 0; i < n; i++)
            cur[i] = head[i];
//        used[s] = used[t] = true;
        for (int i = head[s]; i != -1; i = edges[i].nxt) {
            push(i, true);
            if (exc[edges[i].u] > 0) {
//                if (!used[edges[i].u])
                    have.push(edges[i].u);
//                used[edges[i].u] = true;
            }
        }
        while (!have.empty()) {
            int v = have.front();
            have.pop();
            used[v] = false;
//            cerr << v << ' ' << cur[v] << '\n';
            discharge(v);
            if (exc[v] > 0 && !used[v]) {
                used[v] = true;
                have.push(v);
            }
        }
        return ans;
    }
} // namespace pre_flow



int solve() {
    if (!(cin >> n >> m))
        return 1;
    pre_flow::init();
    pre_flow::s = 0;
    pre_flow::t = n - 1;
    for (int i = 0; i < m; i++) {
        int v, u, w;
        cin >> v >> u >> w;
        pre_flow::add_edge(v - 1, u - 1, w);
    }
    ll a1 = pre_flow::max_flow();
//    cerr << a1 << ' ' << a2 << '\n';
    cout << a1 << '\n';
    for (int i = 0; i < pre_flow::pnt; i += 2)
        cout << pre_flow::edges[i].f << '\n';
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
