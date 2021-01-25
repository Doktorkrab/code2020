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
const int MAXN = 1005;
int arr[MAXN][MAXN];
int dp[MAXN][MAXN];
vector<pair<int, int>> poses[10 * MAXN * MAXN];
vector<pair<int, int>> shift = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
inline bool check(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < m;
}
int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
            poses[arr[i][j]].emplace_back(i, j);
            dp[i][j] = 1;
        }
    for (int i = 2; i <= 10 * n * m; i++){
        for (auto [x, y] : poses[i]) {
            for (auto[sx, sy] : shift) {
                int nx = x + sx, ny = y + sy;
                if (check(nx, ny) && arr[x][y] == arr[nx][ny] + 1)
                    dp[x][y] = max(dp[x][y], dp[nx][ny] + 1);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            ans = max(dp[i][j], ans);
    cout << ans << '\n';
    return 0;
}
 
signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
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
