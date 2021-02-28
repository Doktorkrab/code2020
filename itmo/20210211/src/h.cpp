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

enum {
    EMPTY, START, FINISH, SOURCE, OBJ
};

const int MAXN = 505;
const int SOURCES = 1e3 + 7;
const int INF = 1e11 + 8;
int k, s;
int n, m;
int fld[MAXN][MAXN];
int dist[MAXN][MAXN];
int s_dists[SOURCES][SOURCES];
int dij[SOURCES];
bool used1[SOURCES];
bool used[MAXN][MAXN];
vector<pair<int, int>> sources;
pair<int, int> shift[] = {{-1, 0},
                          {1,  0},
                          {0,  1},
                          {0,  -1}};
int p[MAXN * MAXN];
int sz[MAXN * MAXN];

int find_set(int x) {
    if (p[x] == x)
        return x;
    return p[x] = find_set(p[x]);
}

bool un(int x, int y, int x1, int y1) {
    int a = x * m + y, b = x1 * m + y1;
    a = find_set(a);
    b = find_set(b);
    if (a == b)
        return false;
    if (sz[a] > sz[b])
        swap(a, b);
    p[a] = b;
    sz[b] += sz[a];
    return true;
}

bool check(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < m && fld[x][y] != OBJ;
}

int bfs(int index) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            used[i][j] = false;
            dist[i][j] = INF;
        }
    auto[xs, ys] = sources[index];
    dist[xs][ys] = 0;
    deque<pair<int, int>> q = {{xs, ys}};
    while (!q.empty()) {
        auto[x, y] = q.front();
        q.pop_front();
        if (used[x][y])
            continue;
        used[x][y] = true;
        for (auto[sx, sy] : shift) {
            int nx = x + sx, ny = y + sy;
            if (!check(nx, ny) || dist[x][y] + k > s)
                continue;
            if (dist[nx][ny] > dist[x][y] + k) {
                dist[nx][ny] = dist[x][y] + k;
                q.emplace_back(nx, ny);
            }
        }
    }
    for (int i = 0; i < SZ(sources); i++) {
        auto[x, y] = sources[i];
        s_dists[index][i] = dist[x][y];
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (fld[i][j] == FINISH)
                return dist[i][j];
    assert(0);
}

int solve() {
    if (!(cin >> k >> s >> n >> m))
        return 1;
    sources.clear();
    int xs = -1, ys = -1;
    int kek = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char x;
            cin >> x;
            used[i][j] = false;
            dist[i][j] = INF;
            p[i * m + j] = i * m + j;
            sz[i * m + j] = 1;
            switch (x) {
                case '@': {
                    xs = i, ys = j;
                    fld[i][j] = START;
                    kek = SZ(sources);
                    sources.emplace_back(i, j);
                    dist[i][j] = 0;
                    break;
                }
                case '#': {
                    fld[i][j] = OBJ;
                    break;
                }
                case '.': {
                    fld[i][j] = EMPTY;
                    break;
                }
                case 'E': {
                    fld[i][j] = FINISH;
                    break;
                }
                case '$': {
                    fld[i][j] = SOURCE;
                    sources.emplace_back(i, j);
                    dist[i][j] = 0;
                    break;
                }
                default:
                    assert(0);
            }
        }
    }

    deque<pair<int, int>> q = {ALL(sources)};
    while (!q.empty()) {
        auto[x, y] = q.front();
        q.pop_front();
        if (used[x][y])
            continue;
        used[x][y] = true;

        for (auto[sx, sy] : shift) {
            int nx = x + sx, ny = y + sy;
            if (!check(nx, ny) || dist[x][y] + k > s)
                continue;
            if (dist[nx][ny] != INF && dist[nx][ny] + dist[x][y] + k <= s)
                un(nx, ny, x, y);
            if (dist[nx][ny] > dist[x][y] + k) {
                dist[nx][ny] = dist[x][y] + k;
                q.emplace_back(nx, ny);
            }
        }
    }
    vector<pair<int, int>> t;
    int x = find_set(xs * m + ys);
    for (auto[a, b] : sources) {
        if (x == find_set(a * m + b))
            t.emplace_back(a, b);
    }

    swap(sources, t);
//    for (auto [a, b] : sources)
//        cout << a << ' ' << b << '\n';
    for (int i = 0; i < SZ(sources); i++)
        bfs(i);
    fill(dij, dij + SZ(sources), INF);
    fill(used1, used1 + SZ(sources), false);
    kek = find(ALL(sources), make_pair(xs, ys)) - sources.begin();
    dij[kek] = 0;
    for (int i = 0; i < SZ(sources); i++) {
        int v = -1;
        for (int j = 0; j < SZ(sources); j++) {
            if (!used1[j] && (v == -1 || dij[v] > dij[j]))
                v = j;
        }
        if (v == -1)
            break;
        used1[v] = true;
        for (int j = 0; j < SZ(sources); j++) {
            if (dij[j] > dij[v] + s_dists[v][j])
                dij[j] = dij[v] + s_dists[v][j];
        }
    }
    int ans = INF;
    for (int i = 0; i < SZ(sources); i++)
        ans = min(ans, dij[i] + bfs(i));
    if (ans >= INF)
        cout << "IMPOSSIBLE\n";
    else
        cout << ans << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("h.in", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
//    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
//#ifdef LOCAL
//        cout << "------------------------------\n";
//#endif
    }
}
