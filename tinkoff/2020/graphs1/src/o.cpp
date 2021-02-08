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
int sx, sy;
int max_l, max_r;
const int MAXN = 2e3 + 7;
const int INF = 1e9;
int arr[MAXN][MAXN];
bool used[MAXN][MAXN];
int dist[MAXN][MAXN];
pair<int, int> shift[] = {{-1, 0},
                          {1,  0},
                          {0,  -1},
                          {0,  1}};

inline bool check(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && arr[x][y];
}

int solve() {
    if (!(cin >> n >> m >> sx >> sy >> max_l >> max_r))
        return 1;
    --sx, --sy;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            char x;
            cin >> x;
            arr[i][j] = (x == '.');
            dist[i][j] = INF;
        }
    deque<pair<int, int>> q = {{sx, sy}};
    dist[sx][sy] = 0;
    int ans = 0;
    while (SZ(q)) {
        auto[x, y] = q.front();
        q.pop_front();
        if (used[x][y])
            continue;
        used[x][y] = true;
        int l = dist[x][y] - y + sy;
//        cout << x + 1 << ' ' << y + 1 << ' ' << l << ' ' << dist[x][y] << '\n';
        if (l <= max_l && dist[x][y] <= max_r)
            ans++;
        for (auto[shx, shy] : shift) {
            int nx = x + shx, ny = y + shy;
            if (!check(nx, ny))
                continue;
            if (dist[nx][ny] > dist[x][y] + (shy == 1)) {
                dist[nx][ny] = dist[x][y] + (shy == 1);
                if (shy == 1)
                    q.emplace_back(nx, ny);
                else
                    q.emplace_front(nx, ny);
            }
        }
    }
    cout << ans << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("o.in", "r", stdin);
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
