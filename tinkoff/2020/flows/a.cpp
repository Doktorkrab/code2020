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

struct Edge {
    int v = 0, u = 1;
    ll c = 0, f = 0;
    int nxt = -1;
};
int n, m;
const int MAXN = 5e2 + 7;
const int MAXM = 1e4 + 7;
Edge edges[2 * MAXM];
int head[MAXN];
int head_changed[MAXN];
int d[MAXN];
int s, t;

void bfs(const int MAX) {
    fill(d, d + n, -1);
    d[s] = 0;
    deque<int> q = {s};
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (int e = head[v]; e != -1; e = edges[e].nxt) {
            auto[_, u, c, f, nxt] = edges[e];
            if (c - f >= MAX && d[u] == -1) {
                d[u] = d[v] + 1;
                q.push_back(u);
            }
        }
    }
}

ll dfs(int v, ll min_flow) {
    if (v == t || min_flow == 0)
        return min_flow;
    for (int &id = head_changed[v]; id != -1; id = edges[id].nxt) {
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

int solve() {
    if (!(cin >> n >> m))
        return 1;
    s = 0, t = n - 1;
    fill(head, head + n, -1);
    int pnt = 0;
    for (int i = 0; i < m; i++) {
        int v, u, w;
        cin >> v >> u >> w;
        --v, --u;
        edges[pnt] = {v, u, w, 0, head[v]};
        head[v] = pnt++;
        edges[pnt] = {u, v, 0, 0, head[u]};
        head[u] = pnt++;
    }
    ll ans = 0;
    ll fl = 0;
    for (int power = 30; power >= 0; power--) {
        while (1) {
            bfs(1 << power);
            if (d[t] == -1)
                break;
            copy(head, head + n, head_changed);
            while (fl = dfs(s, TMAX(int)))
                ans += fl;
        }
    }
    cout << ans << '\n';
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
