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
int matrix[MAXN][MAXN];
int prefix_row[MAXN][MAXN];
int prefix_column[MAXN][MAXN];
int ans[MAXN][MAXN];
pair<int, int> from[MAXN][MAXN];

int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
            prefix_row[i][j + 1] = prefix_row[i][j] + matrix[i][j];
            prefix_column[i + 1][j] = prefix_column[i][j] + matrix[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int a = (j ? ans[i][j - 1] : 0) + abs(prefix_column[i + 1][j]);
            int b = (i ? ans[i - 1][j] : 0) + abs(prefix_row[i][j + 1]);
            if (a > b) {
                from[i][j] = {0, prefix_column[i + 1][j] < 0};
                ans[i][j] = a;
            } else {
                from[i][j] = {1, prefix_row[i][j + 1] < 0};
                ans[i][j] = b;
            }
        }
    }
//    for (int i = 0; i < n; i++)
//        for (int j = 0; j < m; j++)
//            cout << ans[i][j] << " \n"[j + 1 == m];
//    for (int i = 0; i < n; i++)
//        for (int j = 0; j < m; j++)
//            cout << "(" << from[i][j].first << ", " << from[i][j].second << ")" << " \n"[j + 1 == m];
    cout << ans[n - 1][m - 1] << '\n';
    int x = n - 1;
    int y = m - 1;
    bool rev = false;
    vector<pair<int, int>> ans;
    while (0 <= x && 0 <= y) {
        if (rev != from[x][y].second) {
            ans.emplace_back(x, y);
            rev ^= 1;
        }
        if (!from[x][y].first)
            y--;
        else
            x--;
    }
    reverse(ALL(ans));
    cout << SZ(ans) << '\n';
    for (auto[x, y] : ans)
        cout << x + 1 << ' ' << y + 1 << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("g.in", "r", stdin);
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
