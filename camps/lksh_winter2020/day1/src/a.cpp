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

const int MAXN = 4005;
const int MAXK = 805;

int n, k;
ll dp[MAXK][MAXN];
int opt[MAXK][MAXN];
int mat[MAXN][MAXN];

inline int get(int i, int j) {
    int ans = mat[j][j];
    if (i > 0) {
        ans -= mat[i - 1][j] + mat[j][i - 1];
        ans += mat[i - 1][i - 1];
    }
    return ans;
}

void rec(int level, int tl, int tr, int l, int r) {
    if (tr < tl)
        return;
    int tm = (tl + tr) / 2;
    dp[level][tm] = TMAX(int);
    for (int x = l; x <= min(tm - 1, r); x++) {
        ll now = dp[level - 1][x] + get(x + 1, tm);
        if (dp[level][tm] > now) {
            dp[level][tm] = now;
            opt[level][tm] = x;
        }
    }
    if (tl == tr)
        return;
    rec(level, tl, tm - 1, l, opt[level][tm]);
    rec(level, tm + 1, tr, opt[level][tm], r);
}

int solve() {
    if (!(cin >> n >> k))
        return 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];
            if (i > 0 && j > 0)
                mat[i][j] -= mat[i - 1][j - 1];
            if (i > 0)
                mat[i][j] += mat[i - 1][j];
            if (j > 0)
                mat[i][j] += mat[i][j - 1];
        }
    for (int i = 0; i < n; i++)
        dp[1][i] = get(0, i);
    for (int i = 2; i <= k; i++)
        rec(i, 0, n - 1, 0, n - 1);
    cout << dp[k][n - 1] / 2 << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("a.in", "r", stdin);
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
