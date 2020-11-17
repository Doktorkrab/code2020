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

const pair<int, int> shift[] = {{-1, 0},
                                {0,  1},
                                {1,  0},
                                {0,  -1}};

int n, m;
const int MAXN = 75;
const int MAXV = MAXN * MAXN + 2;
const int MAXE = 6 * MAXV;
Edge edges[2 * MAXE];
int head[MAXV];
int head_changed[MAXV];
int d[MAXV];
int s, t;
int now_edge = 0;

void add_edge(int v, int u, int c) {
    edges[now_edge] = {v, u, c, 0, head[v]};
    head[v] = now_edge++;
    edges[now_edge] = {u, v, 0, 0, head[u]};
    head[u] = now_edge++;
}

void bfs(const int MAX) {
    fill(d, d + MAXV, -1);
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

int fld[MAXN][MAXN];
int w, b, g;

int solve() {
    if (!(cin >> n >> m >> w >> b >> g))
        return 1;
    fill(head, head + MAXV, -1);
    now_edge = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            char x;
            cin >> x;
            fld[i][j] = (x == 'W');
        }
    s = n * m;
    t = n * m + 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            int now = i * m + j;
            if (fld[i][j]) {
                add_edge(s, now, b);
            } else {
                add_edge(now, t, w);
            }
            for (const auto&[sx, sy] : shift) {
                int x = i + sx;
                int y = j + sy;
                if (0 <= x && x < n && 0 <= y && y < m)
                    add_edge(now, x * m + y, g);
            }
        }
    ll ans = 0, now;
    for (int power = 30; power >= 0; power--) {
        while (1) {
            bfs(1 << power);
            if (d[t] == -1)
                break;
            copy(head, head + MAXV, head_changed);
            while (now = dfs(s, TMAX(int)))
                ans += now;
        }
    }
//    for (int i = 0; i < now_edge; i += 2) {
//        const auto &e = edges[i];
//        if (e.v == s)
//            cout << "s";
//        else
//            cout << "(" << e.v / m + 1 << ", " << e.v % m + 1 << ")";
//        cout << "->";
//        if (e.u == t)
//            cout << "t";
//        else
//            cout << "(" << e.u / m + 1 << ", " << e.u % m + 1 << ")";
//        cout << ' ' << e.f << "/" << e.c << '\n';
//
//    }
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
