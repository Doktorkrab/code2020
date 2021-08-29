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

int n;
string s;
const int MAXN = 5e3 + 7;
int dp[MAXN];
int lcp[MAXN][MAXN];

int solve() {
    if (!(cin >> n >> s))
        return 1;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            lcp[i][j] = 0;
    for (int i = n - 1; i >= 0; i--)
        for (int j = n - 1; j >= 0; j--) {
            if (i == j)
                lcp[i][j] = n - i;
            else if (s[i] == s[j])
                lcp[i][j] = lcp[i + 1][j + 1] + 1;
        }
    for (int i = 0; i < n; i++)
        dp[i] = n - i;
    for (int i = 1; i < n; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (lcp[i][j] == (n - i) || (lcp[i][j] != (n - j) && s[i + lcp[i][j]] > s[j + lcp[i][j]]))
                dp[i] = max(dp[i], dp[j] + (n - i - lcp[i][j]));
        }
    }
//    for (int i = 0; i < n; i++)
//        cout << dp[i] << " \n"[i + 1 == n];
    cout << (*max_element(dp, dp + n)) << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("e.in", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tests = 1e9;
    cin >> tests;
    for (int i = 1; i <= tests; i++) {
        if (solve())
            break;
#ifdef LOCAL
        cout << "------------------------------\n";
#endif
    }
}
