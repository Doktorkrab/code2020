#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;
using ld = long double;

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
const int MAXN = 800;
ll dist[MAXN][MAXN];
int n, m;
pair<int, int> people[MAXN];
pair<int, int> points[MAXN];
int a[MAXN];

namespace flow {
    struct Edge {
        int v = 0, u = 1;
        ll c = 0, f = 0;
        int nxt = -1;
    };
    const int MAXN = 500 * 2;
    const int MAXM = 500 * 500 + 500 + 500 + 123;
    Edge edges[2 * MAXM];
    int head[MAXN];
    int head_changed[MAXN];
    int d[MAXN];
    int s, t;
    int pnt = 0;
    int v_cnt = 0;
    ll max_dist;
    deque<int> q;

    void init() {
        pnt = 0;
        fill(head, head + MAXN, -1);
    }

    bool check(const Edge &e) {
        if (e.v < n && e.u >= n && e.u < n + m) {
            int v = e.v;
            int u = e.u - n;
            return dist[v][u] <= max_dist;
        }
        return true;
    }

    void bfs(const int MAX) {
        fill(d, d + v_cnt, -1);
        d[s] = 0;
        q.clear();
        q.push_back(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop_front();
            for (int e = head[v]; e != -1; e = edges[e].nxt) {
                auto&[_, u, c, f, nxt] = edges[e];
                if (check(edges[e]) && c - f >= MAX && d[u] == -1) {
                    d[u] = d[v] + 1;
                    q.push_back(u);
                }
            }
        }
    }

    ll dfs(int v, ll min_flow) {
        if (v == t)
            return min_flow;
        for (int &id = head_changed[v]; id != -1; id = edges[id].nxt) {
            const auto &e = edges[id];
            if (e.c - e.f <= 0 || !check(e))
                continue;
            ll res = dfs(e.u, min(min_flow, e.c - e.f));
            if (res > 0) {
                edges[id].f += res;
                edges[id ^ 1].f -= res;
                return res;
            }
        }
        return 0;
    }

    void add_edge(int v, int u, int w) {
//        cout << v << "->" << u << ' ' << w << '\n';
        edges[pnt] = {v, u, w, 0, head[v]};
        head[v] = pnt++;
        edges[pnt] = {u, v, 0, 0, head[u]};
        head[u] = pnt++;
        assert(pnt <= 2 * MAXM);
    }

    ll max_flow() {
        ll ans = 0;
        ll fl = 0;
        assert(v_cnt <= MAXN);
        copy(head, head + v_cnt, head_changed);
        while (fl = dfs(s, TMAX(int))) {
            ans += fl;
        }
        return ans;
    }

    void clear() {
        for (int i = 0; i < pnt; i++) {
            auto &e = edges[i];
            e.f = 0;
        }
    }
}  // namespace flow


bool check(ll x) {
    flow::max_dist = x;
    flow::clear();
    return flow::max_flow() == n;
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    flow::init();
    flow::v_cnt = n + m + 2;
    for (int i = 0; i < n; i++)
        cin >> people[i].first >> people[i].second;
    for (int i = 0; i < m; i++)
        cin >> points[i].first >> points[i].second >> a[i];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            ll x = people[i].first - points[j].first;
            ll y = people[i].second - points[j].second;
            dist[i][j] = x * x + y * y;
            flow::add_edge(i, j + n, 1);
        }

    flow::s = n + m;
    flow::t = n + m + 1;
    for (int i = 0; i < n; i++)
        flow::add_edge(flow::s, i, 1);
    for (int i = 0; i < m; i++)
        flow::add_edge(i + n, flow::t, a[i]);
    if (check(0)) {
        cout << "0\n";
        return 0;
    }
    ll l = 0, r = 3e12 + 1;
    while (r - l > 1) {
        ll mid = l + (r - l) / 2;
        if (check(mid))
            r = mid;
        else
            l = mid;
    }
    cout << fixed << setprecision(20) << sqrtl(r * 1.L) << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("f.in", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1;
//    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}
