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
namespace flow {
    struct Edge {
        int v = 0, u = 1;
        ll c = 0, f = 0;
        int nxt = -1;
    };
    const int MAXN = 2e4 + 7;
    const int MAXM = 3e4 + 7;
    Edge edges[2 * MAXM];
    int head[MAXN];
    int head_changed[MAXN];
    int d[MAXN];
    int s, t;
    int pnt = 0;

    void init() {
        pnt = 0;
        fill(head, head + MAXN, -1);
    }

    void bfs(const int MAX) {
        fill(d, d + MAXN, -1);
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

    void add_edge(int v, int u, int w) {
//        cout << v << "->" << u << ' ' << w << '\n';
        edges[pnt] = {v, u, w, 0, head[v]};
        head[v] = pnt++;
        edges[pnt] = {u, v, 0, 0, head[u]};
        head[u] = pnt++;
    }

    ll max_flow() {
        ll ans = 0;
        ll fl = 0;
        for (int power = 30; power >= 0; power--) {
            while (1) {
                bfs(1 << power);
                if (d[t] == -1)
                    break;
                copy(head, head + MAXN, head_changed);
                while (fl = dfs(s, TMAX(int)))
                    ans += fl;
            }
        }
        return ans;
    }
}  // namespace flow

bool check(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < m;
}

const pair<int, int> shift[] = {{-1, 0},
                                {0,  -1},
                                {0,  1},
                                {1,  0}};
const int MAXN = 75;
int arr[MAXN][MAXN];
int hor[MAXN][MAXN];
int ver[MAXN][MAXN];
int edges[4][MAXN][MAXN];

int solve() {
    if (!(cin >> n >> m))
        return 1;
    flow::init();
    flow::s = n * m;
    flow::t = n * m + 1;
    int fake_pos = n * m + 2;
    int need = 0;
    int need1 = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
            if ((i + j) & 1) {
                flow::add_edge(i * m + j, flow::t, arr[i][j]);
                need += arr[i][j];
            } else {
                flow::add_edge(flow::s, i * m + j, arr[i][j]);
                need1 += arr[i][j];
            }
            for (int k = 0; k < 4; k++)
                edges[k][i][j] = -1;
        }
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (arr[i][j] == 2) {
                if ((i + j) & 1) {
                    flow::add_edge(fake_pos, i * m + j, 1);
                    flow::add_edge(fake_pos + 1, i * m + j, 1);
                } else {
                    flow::add_edge(i * m + j, fake_pos, 1);
                    flow::add_edge(i * m + j, fake_pos + 1, 1);
                }
                hor[i][j] = fake_pos;
                ver[i][j] = fake_pos + 1;
                fake_pos += 2;
            } else {
                hor[i][j] = ver[i][j] = i * m + j;
            }
        }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((i + j) & 1)
                continue;
            for (int k = 0; k < 4; k++) {
                auto[s_x, s_y] = shift[k];
                int x = i + s_x, y = j + s_y;
                if (!check(x, y))
                    continue;
                edges[k][i][j] = edges[3 - k][x][y] = flow::pnt;
                if (k == 0 || k == 3)
                    flow::add_edge(ver[i][j], ver[x][y], 1);
                else
                    flow::add_edge(hor[i][j], hor[x][y], 1);
            }
        }
    }
    int fl = flow::max_flow();
    if (fl != need || fl != need1) {
        cout << "Impossible!\n";
        return 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << ".";
            if (edges[0][i][j] >= 0 && flow::edges[edges[0][i][j]].f == 1)
                cout << "X";
            else
                cout << ".";
            cout << ".";
        }
        cout << '\n';
        for (int j = 0; j < m; j++) {
            if (edges[1][i][j] >= 0 && flow::edges[edges[1][i][j]].f == 1)
                cout << "X";
            else
                cout << ".";
            if (arr[i][j] > 0)
                cout << "O";
            else
                cout << ".";
            if (edges[2][i][j] >= 0 && flow::edges[edges[2][i][j]].f == 1)
                cout << "X";
            else
                cout << ".";
        }
        cout << '\n';
        for (int j = 0; j < m; j++) {
            cout << ".";
            if (edges[3][i][j] >= 0 && flow::edges[edges[3][i][j]].f == 1)
                cout << "X";
            else
                cout << ".";
            cout << ".";
        }
        cout << '\n';
    }
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
