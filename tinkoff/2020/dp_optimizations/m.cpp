#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
int n, k;
const int MAXN = 4005;
const int MAXK = 805;
int dp[MAXK][MAXN];
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

void rec(int level, int tl, int tr, int min_v, int max_v) {
    if (tr < tl) return;
    // cerr << level << ' ' << tl << ' ' << tr << ' ' << min_v << ' ' << max_v <<
    // '\n';
    int tm = (tl + tr) / 2;
    dp[level][tm] = 0x3f3f3f3f;
    for (int v = min_v; v <= min(tm - 1, max_v); v++) {
        int now = dp[level - 1][v] + get(v + 1, tm);
        if (dp[level][tm] > now) {
            dp[level][tm] = now;
            opt[level][tm] = v;
        }
    }
    // cerr << '\t' << level << ' ' << tm << ' ' << dp[level][tm] << '\n';
    if (tl == tr) return;
    rec(level, tl, tm - 1, min_v, opt[level][tm]);
    rec(level, tm + 1, tr, opt[level][tm], max_v);
}

inline void init() {}

inline void solve() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];
            if (i > 0 && j > 0) mat[i][j] -= mat[i - 1][j - 1];
            if (i > 0) mat[i][j] += mat[i - 1][j];
            if (j > 0) mat[i][j] += mat[i][j - 1];
        }

    for (int i = 0; i < n; i++) dp[1][i] = get(0, i);
    for (int i = 2; i <= k; i++) rec(i, 0, n - 1, 0, n - 1);
    cout << dp[k][n - 1] / 2 << '\n';
}

int main() {
#ifdef LOCAL
    freopen("I.in", "r", stdin);
    freopen("I.out", "w", stdout);
#endif

    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    while (cin >> n >> k) solve();
}
