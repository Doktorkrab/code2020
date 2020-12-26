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
const int MAXN = 300;
const ll INF = 1e18;
ll fld[MAXN][MAXN];
int fld1[MAXN][MAXN];
ll d[MAXN][MAXN];
bool used[MAXN][MAXN];
ll frst[MAXN][MAXN];
bool on_cycle[MAXN][MAXN];

int get(char c) {
    if (c == 'U')
        return 0;
    if (c == 'D')
        return 1;
    if (c == 'L')
        return 2;
    return 3;
}

pair<int, int> shift[] = {{-1, 0},
                          {1,  0},
                          {0,  -1},
                          {0,  1}};
int xv, yv;
int xc, yc;
int c_len = -1;

bool check(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < m;
}

void find_cycle() {
    int nx = xc, ny = yc;
    int t = 0;
    while (check(nx, ny) && frst[nx][ny] == -1) {
        frst[nx][ny] = t++;
        auto[sx, sy] = shift[fld1[nx][ny]];
        nx += sx;
        ny += sy;
    }
    if (!check(nx, ny))
        return;
    c_len = t - frst[nx][ny];
    while (!on_cycle[nx][ny]) {
        on_cycle[nx][ny] = true;
        auto[sx, sy] = shift[fld1[nx][ny]];
        nx += sx;
        ny += sy;
    }
}

void dijkstra() {
    priority_queue<pair<ll, pair<int, int>>, vector<pair<ll, pair<int, int>>>, greater<>> q;
    d[xv][yv] = 0;
    q.emplace(0, make_pair(xv, yv));
    while (SZ(q)) {
        auto[dd, xy] = q.top();
        q.pop();
        auto[x, y] = xy;
        if (used[x][y])
            continue;
        used[x][y] = true;
        for (auto[sx, sy] : shift) {
            int nx = x + sx, ny = y + sy;
            if (check(nx, ny) && d[nx][ny] > d[x][y] + fld[nx][ny]) {
                d[nx][ny] = d[x][y] + fld[nx][ny];
                q.emplace(d[nx][ny], make_pair(nx, ny));
            }
        }
    }
}

int solve() {
    if (!(cin >> n >> m >> xv >> yv >> xc >> yc))
        return 1;
    xv--, yv--, xc--, yc--;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cin >> fld[i][j];
            d[i][j] = INF;
        }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            fld1[i][j] = get(c);
            frst[i][j] = -1;
        }

    dijkstra();
    find_cycle();
    ll ans = INF;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (frst[i][j] == -1)
                continue;
            if (!on_cycle[i][j]) {
                if (d[i][j] > frst[i][j])
                    continue;
                ans = min(ans, frst[i][j]);
                continue;
            }
            ll x = max(0LL, (d[i][j] - frst[i][j] + c_len - 1) / c_len);

            ans = min(ans, frst[i][j] + c_len * x);
        }
    }
    if (ans == INF)
        cout << "-1\n";
    else
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
