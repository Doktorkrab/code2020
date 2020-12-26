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

int n, k, m;
const int MAXN = 2e5 + 7;
int p[MAXN];
int dp[MAXN];

int solve() {
    if (!(cin >> n >> k >> m))
        return 1;
    for (int i = 0; i < m; i++)
        cin >> p[i];
    sort(p, p + m);
    for (int i = 0; i < m; ++i) {
        int j = upper_bound(p, p + i, p[i] - k) - p;
        if (j == 0) {
            dp[i] = min(k, p[i]);
        } else {
            dp[i] = dp[j - 1] + min(k, p[i]);
        }
    }
    int ans = dp[m - 1];
    for (int i = 0; i < m; ++i) {
        if (p[m - 1] - p[i] < k) {
            ans = min(ans, (i == 0 ? 0 : dp[i - 1]) + min(k, n - p[i] + 1));
        }
    }
    cout << n - ans << '\n';
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
