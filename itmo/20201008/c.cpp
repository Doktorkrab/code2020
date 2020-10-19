//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx2")

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

int sum(int x, int y) { return x + y < MOD ? x + y : x + y - MOD; }
int mul(int x, int y) { return x * 1LL * y % MOD; }
int qp(int x, int k) {
    int res = 1;
    while (k) {
        if (k & 1) {
            res = mul(res, x);
        }
        x = mul(x, x);
        k >>= 1;
    }
    return res;
}

const int N = 5007;

int n, m;
char s[N];
pair<int, int> q[N];
int cnt[N];
int dp[N][N];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
        s[i] -= '0';
    }
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> q[i].first >> q[i].second;
        --q[i].first, --q[i].second;
    }
    sort(q, q + m, [](pair<int, int> a, pair<int, int> b) {
        return make_tuple(a.second, -a.first) < make_tuple(b.second, -b.first);
    });
    for (int i = 1; i < m; ++i) {
        if (q[i].second == q[i - 1].second) {
            cnt[i] = cnt[i - 1] + 1;
        }
    }
    for (int j = 0; j <= m; ++j) {
        dp[0][j] = qp(2, j);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (q[j - 1].second < i - 1) {
                dp[i][j] = s[i - 1] * dp[i - 1][j];
            } else {
                dp[i][j] = sum(sum(s[i - 1] * dp[i - 1][j], dp[i][j - 1]),
                               mul(dp[q[j - 1].first][j - 1], qp(2, cnt[j - 1])));
            }
        }
    }
    cout << dp[n][m] << '\n';
    // system("pause");
    return 0;
}