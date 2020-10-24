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
const int MAXN = 305;
const int INF = 1e9;
char fld[MAXN][MAXN];
int dp[MAXN][MAXN][2 * MAXN];
bool good[MAXN][MAXN][2 * MAXN];
int lst[MAXN][MAXN][MAXN];

struct Triple {
    int x, y, k;
};
deque<Triple> poses[MAXN];

int solve() {
    if (!(cin >> n >> m))
        return 1;
    for (int i = n - 1; i >= 0; i--)
        for (int j = 0; j < m; j++) {
            cin >> fld[i][j];
            for (int k = 0; k < MAXN; k++) {
                dp[i][j][k] = -INF;
                lst[i][j][k] = -1;
            }
        }
    int pos = find(fld[0], fld[0] + m, 'M') - fld[0];
    dp[0][pos][0] = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k <= n; k++) {
                if (fld[i][j] == '*' || fld[i][j] == '.') {
                    int mx = -INF;
                    if (fld[i - 1][j] != '*')
                        mx = dp[i - 1][j][k];
                    if (j - 1 >= 0 && fld[i - 1][j - 1] != '*')
                        mx = max(mx, dp[i - 1][j - 1][k]);
                    if (j + 1 < m && fld[i - 1][j + 1] != '*')
                        mx = max(mx, dp[i - 1][j + 1][k]);
                    dp[i][j][k] = mx;
                }
                if (fld[i][j] == '(' && k >= 1) {
                    int mx = -INF;
                    if (fld[i - 1][j] != '*')
                        mx = dp[i - 1][j][k - 1];
                    if (j - 1 >= 0 && fld[i - 1][j - 1] != '*')
                        mx = max(mx, dp[i - 1][j - 1][k - 1]);
                    if (j + 1 < m && fld[i - 1][j + 1] != '*')
                        mx = max(mx, dp[i - 1][j + 1][k - 1]);
                    dp[i][j][k] = mx + 1;
                }
                if (fld[i][j] == ')' && k + 1 <= n) {
                    int mx = -INF;
                    if (fld[i - 1][j] != '*')
                        mx = dp[i - 1][j][k + 1];
                    if (j - 1 >= 0 && fld[i - 1][j - 1] != '*')
                        mx = max(mx, dp[i - 1][j - 1][k + 1]);
                    if (j + 1 < m && fld[i - 1][j + 1] != '*')
                        mx = max(mx, dp[i - 1][j + 1][k + 1]);
                    dp[i][j][k] = mx + 1;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (fld[i][j] == '*' || i + 1 == n) {
                if (ans < dp[i][j][0]) {
//                    cout << i << ' ' << j << ' ' << '\n';
                    ans = dp[i][j][0];
                }
            }
    deque<Triple> layer;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if ((fld[i][j] == '*' || i + 1 == n) && dp[i][j][0] == ans) {
                layer.push_back({i, j, 0});
            }
    while (SZ(layer)) {
        auto[a, b, c] = layer.front();
        layer.pop_front();
        if (good[a][b][c])
            continue;
        good[a][b][c] = true;
        if (a == 0)
            continue;
        int nxt = c;
        int add = 0;
        if (fld[a][b] == '(') {
            nxt--;
            add = 1;
        }
        if (fld[a][b] == ')') {
            nxt++;
            add = 1;
        }
        assert(nxt >= 0 && nxt <= n);
        if (b + 1 < m && fld[a - 1][b + 1] != '*' && dp[a - 1][b + 1][nxt] + add == dp[a][b][c])
            layer.push_back({a - 1, b + 1, nxt});
        if (b - 1 >= 0 && fld[a - 1][b - 1] != '*' && dp[a - 1][b - 1][nxt] + add == dp[a][b][c])
            layer.push_back({a - 1, b - 1, nxt});
        if (fld[a - 1][b] != '*' && dp[a - 1][b][nxt] + add == dp[a][b][c])
            layer.push_back({a - 1, b, nxt});
    }

    vector<char> ans1(ans);

    poses[0].push_back({0, pos, 0});
    for (int l = 0; l < ans; l++) {
        bool was_open = 0;
        vector<Triple> nxt;
//        cout << "?" << poses[l].size() << ' ' << l << '\n';
        while (SZ(poses[l])) {
            auto[a, b, c] = poses[l].front();
//            cout << a << ' ' << b << ' ' << c << '\n';
//            assert(good[a][b][c]);
            poses[l].pop_front();
            if (lst[a][b][c] >= l)
                continue;
            lst[a][b][c] = l;
            if (a + 1 >= n || fld[a][b] == '*')
                continue;
            if (c + 1 <= n) {
                if (fld[a + 1][b] == '(' && good[a + 1][b][c + 1] && dp[a + 1][b][c + 1] == dp[a][b][c] + 1) {
                    was_open = true;
//                    if (l == 2)
//                        cout << a << ' ' << b << ' ' << c << '\n';
                    poses[l + 1].push_back({a + 1, b, c + 1});
                }
                if (b + 1 < m && fld[a + 1][b + 1] == '(' && good[a + 1][b + 1][c + 1] &&
                    dp[a + 1][b + 1][c + 1] == dp[a][b][c] + 1) {
                    was_open = true;
//                    if (l == 2)
//                        cout << a << ' ' << b << ' ' << c << '\n';
                    poses[l + 1].push_back({a + 1, b + 1, c + 1});
                }
                if (b - 1 >= 0 && fld[a + 1][b - 1] == '(' && good[a + 1][b - 1][c + 1] &&
                    dp[a + 1][b - 1][c + 1] == dp[a][b][c] + 1) {
                    was_open = true;
//                    if (l == 2)
//                        cout << a << ' ' << b << ' ' << c << '\n';
                    poses[l + 1].push_back({a + 1, b - 1, c + 1});
                }
            }
            if (fld[a + 1][b] == '.' && good[a + 1][b][c] && dp[a + 1][b][c] == dp[a][b][c])
                poses[l].push_back({a + 1, b, c});
            if (b + 1 < m && fld[a + 1][b + 1] == '.' && good[a + 1][b + 1][c] && dp[a + 1][b + 1][c] == dp[a][b][c])
                poses[l].push_back({a + 1, b + 1, c});
            if (b - 1 >= 0 && fld[a + 1][b - 1] == '.' && good[a + 1][b - 1][c] && dp[a + 1][b - 1][c] == dp[a][b][c])
                poses[l].push_back({a + 1, b - 1, c});
            if (c - 1 >= 0) {
                if (fld[a + 1][b] == ')' && good[a + 1][b][c - 1] && dp[a + 1][b][c - 1] == dp[a][b][c] + 1) {
                    nxt.push_back({a + 1, b, c - 1});
                }
                if (b + 1 < m && fld[a + 1][b + 1] == ')' && good[a + 1][b + 1][c - 1] &&
                    dp[a + 1][b + 1][c - 1] == dp[a][b][c] + 1) {
                    nxt.push_back({a + 1, b + 1, c - 1});
                }
                if (b - 1 >= 0 && fld[a + 1][b - 1] == ')' && good[a + 1][b - 1][c - 1] &&
                    dp[a + 1][b - 1][c - 1] == dp[a][b][c] + 1) {
                    nxt.push_back({a + 1, b - 1, c - 1});
                }
            }
        }
//        cout << l << ' ' << was_open << "!\n";
        if (was_open)
            ans1[l] = '(';
        else {
//            cerr << l << '\n';
//            assert(SZ(nxt));
            ans1[l] = ')';
            for (auto x : nxt)
                poses[l + 1].push_back(x);
        }
    }
    cout << ans << '\n';
//    int bal = 0;
    for (char c : ans1) {
//        if (c == '(')
//            bal++;
//        if (c == ')')
//            bal--;
//        assert(bal >= 0);
        cout << c;
    }
//    assert(bal == 0);
    cout << '\n';
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
