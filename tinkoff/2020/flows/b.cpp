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

int n, m, k, l;
const int MAXN = 55;
const int MAXV = 2 * MAXN * MAXN + 2;  // s, t, cells, fake
const int MAXE = 4 * MAXV + MAXN * MAXN;  // idk
const int INF = 1e9;  // max capacity
pair<int, int> shift[] = {{-1, 0},
                          {1,  0},
                          {0,  1},
                          {0,  -1}};
struct Edge {
    int v = 0, u = 1, c = 0, f = 0, nxt = -1;
};
Edge edges[2 * MAXE];
int now_edge = 0;
int head[MAXV];
int head_changed[MAXV];
int d[MAXV];
bool used[MAXV];
int s, t;

void add_edge(int v, int u, int c) {
    edges[now_edge] = {v, u, c, 0, head[v]};
    head[v] = now_edge++;
    edges[now_edge] = {u, v, 0, 0, head[u]};
    head[u] = now_edge++;
}

void bfs(int MAX) {
    fill(d, d + MAXV, -1);
    d[s] = 0;
    deque<int> q = {s};
    while (SZ(q)) {
        int v = q.front();
        q.pop_front();
        for (int i = head[v]; i != -1; i = edges[i].nxt) {
            const auto &e = edges[i];
            if (d[e.u] == -1 && e.c - e.f >= MAX) {
                d[e.u] = d[v] + 1;
                q.push_back(e.u);
            }
        }
    }
}

int dfs(int v, int flow) {
    if (v == t)
        return flow;
    for (int &id = head_changed[v]; id != -1; id = edges[id].nxt) {
        const auto &e = edges[id];
        if (e.c - e.f == 0 || d[v] + 1 != d[e.u])
            continue;
        int res = dfs(e.u, min(flow, e.c - e.f));
        if (res != 0) {
            edges[id].f += res;
            edges[id ^ 1].f -= res;
            return res;
        }
    }
    return 0;
}

void dfs(int v) {
    used[v] = true;
    for (int id = head[v]; id != -1; id = edges[id].nxt) {
        const auto &e = edges[id];
        if (!used[e.u] && e.c - e.f > 0)
            dfs(e.u);
    }
}

const int ROCK = -1, EMPTY = 0, WALL = 1;
int fld[MAXN][MAXN];

int solve() {
    if (!(cin >> n >> m >> k >> l))
        return 1;
    now_edge = 0;
    fill(head, head + MAXV, -1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            fld[i][j] = EMPTY;


    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        fld[x - 1][y - 1] = ROCK;
    }
    for (int i = 0; i < l; i++) {
        int x, y;
        cin >> x >> y;
        fld[x - 1][y - 1] = WALL;
    }
    int fake_pos = n * m;  // for wall we need 2 vertices
    int xa, ya, xb, yb;
    cin >> xa >> ya >> xb >> yb;
    --xa, --ya, --xb, --yb;
    s = xa * m + ya;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (fld[i][j] == ROCK)
                continue;
            int now = i * m + j;
            if (fld[i][j] == WALL) {
                add_edge(now, fake_pos, 1);
                now = fake_pos++;
            }
            for (auto[sx, sy] : shift) {
                int x = sx + i, y = sy + j;
                if (0 <= x && x < n && 0 <= y && y < m && fld[x][y] != ROCK)
                    add_edge(now, x * m + y, INF);
            }
            if (i == xb && j == yb)
                t = now;
        }
    ll flow = 0, now = 0;
    for (int power = 30; power >= 0; power--) {
        while (true) {
            bfs(1 << power);
            if (d[t] == -1)
                break;
            copy(head, head + MAXV, head_changed);
            while (now = dfs(s, INT_MAX))
                flow += now;
        }
    }
    dfs(s);
    vector<pair<int, int>> ans;
    for (int i = 0; i < now_edge; i++) {
        const auto &e = edges[i];
        if (used[e.v] ^ used[e.u] && e.c == 1) {
            ans.emplace_back(e.v / m + 1, e.v % m + 1);
        }
    }
    if (flow > fake_pos - n * m) {
        cout << "-1\n";
        return 0;
    }
    cout << SZ(ans) << '\n';
//    cout << flow << '\n';
    for (const auto&[x, y] : ans)
        cout << x << ' ' << y << '\n';
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
