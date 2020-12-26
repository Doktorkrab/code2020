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
const int MAXN = 1e3 + 7;
char fld[MAXN][MAXN];
int id[MAXN][MAXN];
int dir[MAXN * MAXN];
int inter[MAXN][MAXN];
vector<int> g[MAXN * MAXN];
pair<pair<int, int>, pair<int, int>> have[MAXN * MAXN];
pair<int, int> shift[] = {{-1, 0},
                          {1,  0},
                          {0,  1},
                          {0,  -1}};
bool bad[MAXN * MAXN];
int comp[MAXN * MAXN];
int parity[MAXN * MAXN];
int sum[2][MAXN * MAXN];
int ans[MAXN * MAXN];
int ans1[MAXN][MAXN];
vector<int> neigh[MAXN * MAXN];
int took[MAXN * MAXN];

void dfs(int v, int c, int p) {
    comp[v] = c;
    parity[v] = p;
    sum[p][c]++;
    for (int u : g[v])
        if (comp[u] == -1)
            dfs(u, c, 1 - p);
}

int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cin >> fld[i][j];
            id[i][j] = -1;
            inter[i][j] = -1;
            g[i * m + j].clear();
            ans1[i][j] = -1;
        }
    int pnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (id[i][j] != -1 || fld[i][j] == '.')
                continue;
            for (auto[a, b] : shift) {
                int x = a + i, y = b + j;
                if (0 <= x && x < n && 0 <= y && y < m && fld[i][j] == fld[x][y]) {
                    id[i][j] = id[x][y] = pnt;
                    have[pnt] = {{i, j},
                                 {x, y}};
                    comp[pnt] = -1;
                    sum[0][pnt] = sum[1][pnt] = 0;
                    parity[pnt] = 0;
                    bad[pnt] = false;
                    took[pnt] = -1;
                    if (x == i)
                        dir[pnt++] = (isupper(fld[i][j]) ? 1 : 0);
                    else
                        dir[pnt++] = (isupper(fld[i][j]) ? 2 : 3);
                }
            }
        }
    for (int i = 0; i < pnt; i++) {
        auto[a, b] = have[i];
        auto[sx, sy] = shift[dir[i]];
        int x = a.first + sx, y = a.second + sy;
        int x1 = b.first + sx, y1 = b.second + sy;
        if (!(0 <= x && x < n && 0 <= y && y < m) || id[x][y] != -1) {
            bad[i] = true;
            continue;
        }
        if (!(0 <= x1 && x1 < n && 0 <= y1 && y1 < m) || id[x1][y1] != -1) {
            bad[i] = true;
            continue;
        }
        if (inter[x][y] != -1) {
            g[inter[x][y]].push_back(i);
            g[i].push_back(inter[x][y]);
        } else
            inter[x][y] = i;
        x = b.first + sx, y = b.second + sy;
        if (inter[x][y] != -1) {
            g[inter[x][y]].push_back(i);
            g[i].push_back(inter[x][y]);
        } else
            inter[x][y] = i;
    }
//    for (int i = 0; i < n; i++)
//        for (int j = 0; j < m; j++)
//            cout << id[i][j] << " \n"[j + 1 == m];
//    cout << "\n";
//    for (int i = 0; i < n; i++)
//        for (int j = 0; j < m; j++)
//            cout << inter[i][j] << " \n"[j + 1 == m];
//    for (int i = 0; i < pnt; i++) {
//        cout << i << ": ";
//        for (int x : g[i])
//            cout << x << ' ';
//        cout << '\n';
//    }
    int c = 0;
    int cnt = 0;
    for (int i = 0; i < pnt; i++) {
        if (comp[i] == -1 && !bad[i]) {
            dfs(i, c, 0);
            if (sum[0][c] > sum[1][c])
                ans[c] = 0, cnt += sum[0][c];
            else
                ans[c] = 1, cnt += sum[1][c];
            c++;
        }
    }
//    cout << "jopa\n";
//    for (int i = 0; i < pnt; i++)
//        cout << comp[i] << " \n"[i + 1 == pnt];
//
//    for (int i = 0; i < pnt; i++)
//        cout << parity[i] << " \n"[i + 1 == pnt];
    for (int i = 0; i < pnt; i++) {
        auto[a, b] = have[i];
//        cout << a.first << ' ' << a.second << ' ' << b.first << ' ' << b.second << '\n';
        ans1[a.first][a.second] = i;
        ans1[b.first][b.second] = i;
        if (bad[i])
            continue;
        if (parity[i] == ans[comp[i]]) {
            auto[sx, sy] = shift[dir[i]];
            int x = a.first + sx, y = a.second + sy;
            ans1[x][y] = i;
            x = b.first + sx, y = b.second + sy;
            ans1[x][y] = i;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (ans1[i][j] == -1)
                continue;
            for (auto[sx, sy] : shift) {
                int x = i + sx, y = j + sy;
                if (!(0 <= x && x < n && 0 <= y && y < m))
                    continue;
                if (ans1[x][y] != -1 && ans1[x][y] != ans1[i][j]) {
                    neigh[ans1[i][j]].push_back(ans1[x][y]);
                    neigh[ans1[x][y]].push_back(ans1[i][j]);
                }
            }
        }
    }
//    for (int i = 0; i < n; i++)
//        for (int j = 0; j < m; j++)
//            if (ans1[i][j] == -1)
//                cout << '.' << " \n"[j + 1 == m];
//            else
//                cout << ans1[i][j] << " \n"[j + 1 == m];
    cout << cnt << '\n';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (ans1[i][j] == -1)
                cout << '.';
            else {
                if (took[ans1[i][j]] != -1) {
                    cout << took[ans1[i][j]];
                    continue;
                }
                vector<bool> check(10);
                for (int x : neigh[ans1[i][j]])
                    if (took[x] != -1)
                        check[took[x]] = true;
                for (int x = 0; x < 10; x++) {
                    if (!check[x]) {
                        cout << (took[ans1[i][j]] = x);
                        break;
                    }
                }
            }
        }
        cout << '\n';
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("e.in", "r", stdin);
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
