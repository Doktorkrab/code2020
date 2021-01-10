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
        int c = 0, f = 0;
        int nxt = -1;
    };
    const int MAXN = 1500;
    const int MAXM = 500*500+500+500 + 10;
    Edge edges[2 * MAXM];
    int head[MAXN];
    int head_changed[MAXN];
    int d[MAXN];
    int s, t;
    int pnt = 0;
    int v_cnt = 0;

    void init() {
        pnt = 0;
        fill(head, head + v_cnt, -1);
    }
    void bfs(const int MAX) {
        fill(d, d + v_cnt, -1);
        d[s] = 0;
        deque<int> q = {s};
        while (!q.empty()) {
            int v = q.front();
            q.pop_front();
            for (int e = head[v]; e != -1; e = edges[e].nxt) {
                auto&[_, u, c, f, nxt] = edges[e];
                if (c - f >= MAX && d[u] == -1) {
                    d[u] = d[v] + 1;
                    q.push_back(u);
                }
            }
        }
    }

    int dfs(int v, int min_flow) {
        if (v == t || min_flow == 0)
            return min_flow;
        for (int& id = head_changed[v]; id != -1; id = edges[id].nxt) {
            const auto &e = edges[id];
            if (e.c - e.f == 0 || d[e.u] != d[v] + 1)
                continue;
            ll res = dfs(e.u, min(min_flow, e.c - e.f));
            if (res != 0) {
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
    int max_flow() {
        int ans = 0;
        int fl = 0;
        assert(v_cnt <= MAXN);
        for (int power = 0; power >= 0; power--) {
            while (1) {
                bfs(1 << power);
                if (d[t] == -1)
                    break;
                copy(head, head + v_cnt, head_changed);
                while (fl = dfs(s, TMAX(int)))
                    ans += fl;
            }
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
    flow::init();
    for (int i = 0; i < n; i++)
        flow::add_edge(flow::s, i, 1);
    for (int i = 0; i < m; i++)
        flow::add_edge(i + n, flow::t, a[i]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (dist[i][j] <= x)
                flow::add_edge(i, j + n, 1);
    return flow::max_flow() == n;
}
ll have[MAXN * MAXN];
int solve() {
    if (!(cin >> n >> m))
        return 1;
    flow::v_cnt = n + m + 2;
    flow::init();
    for (int i = 0; i < n; i++)
        cin >> people[i].first >> people[i].second;
    for (int i = 0; i < m; i++)
        cin >> points[i].first >> points[i].second >> a[i];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            ll x = people[i].first - points[j].first;
            ll y = people[i].second - points[j].second;
            dist[i][j] = x * x + y * y;
            have[i * m + j] = dist[i][j];
        }
    sort(have, have + n * m);
    have[n * m] = 2e12;
    flow::s = n + m;
    flow::t = n + m + 1;
    if (check(have[0])) {
        cout << fixed << setprecision(20) << sqrtl(have[0]) << '\n';
        return 0;
    }
    ll l = 0, r = n * m - 1;
    while (r - l > 1) {
        ll mid = l + (r - l) / 2;
        if (check(have[mid]))
            r = mid;
        else
            l = mid;
    }
    cout << fixed << setprecision(20) << sqrtl(have[r] * 1.L) << '\n';
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
