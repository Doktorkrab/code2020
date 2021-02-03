#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <ctime>
#include <bitset>
#include <complex>

using namespace std;
int n, t;
double p;
const int MAXN = 3e3 + 7;
double dp[MAXN][MAXN];

inline void init() {}

inline void solve() {
    dp[0][0] = 1;
    for (int i = 0; i <= t; i++)
        for (int j = 1; j <= t; j++) {
            dp[i][j] = (1 - p) * dp[i][j - 1];
            if (i)
                dp[i][j] += p * dp[i - 1][j - 1];
        }
    double ans = 0;
    for (int i = 0; i <= t; i++)
        ans += min(i, n) * dp[i][t];
    cout << fixed << setprecision(20) << ans << '\n';
    // for (int i = 0; i <= t; i++)
    //     for (int  j = 0; j <= t; j++)
    //         cerr << fixed << setprecision(5) << dp[i][j] << " \n"[j == t];
}


int main() {
#ifdef LOCAL
    freopen("g.in", "r", stdin);
#endif

    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    while (cin >> n >> p >> t)
        solve();
}
