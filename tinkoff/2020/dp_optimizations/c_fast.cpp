#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;
using ld = long double;

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
#define int ll

int n, k;
const int MAXN = 5e4 + 7;
const int MAXK = 155;
const ll INF = 1e16;

ld dp[MAXK][MAXN];
// int opt[MAXK][MAXN];
ll pref[MAXN];
ll pref2[MAXN];
ll arr[MAXN];

ll cost(int l, int r) {
    return pref[r] - pref[l];
}

ll cost2(int l, int r) {
    return pref2[r] - pref2[l];
}

void div_and_conq(int l, int r, int tl, int tr, int level) {
//    cout << l << ' ' << r << ' ' << tl << ' ' << tr << ' ' << level << '\n';
//    cout << r - l << '\n';
    if (l > r)
        return;
//    cout << "FUCK\n";
    int m = (l + r) / 2;
    int opt = tl;
    for (int i = tl; i <= min(tr, m); i++) {
        ld now = dp[level - 1][i] + cost2(i, m + 1) - 1.L * cost(i, m + 1) * cost(i, m + 1) / (m - i + 1);
        if (now < dp[level][m + 1]) {
            dp[level][m + 1] = now;
            opt = i;
        }
    }
    div_and_conq(l, m - 1, tl, opt, level);
    div_and_conq(m + 1, r, opt, tr, level);
}

int solve() {
    if (!(cin >> n >> k))
        return 1;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(arr, arr + n);

    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + arr[i];
        pref2[i + 1] = pref2[i] + arr[i] * arr[i];
    }
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= k; j++) {
            dp[j][i] = INF;
//            opt[i][j] = n;
        }
    dp[0][0] = 0;

    for (int i = 1; i <= k; i++)
        div_and_conq(0, n, 0, n, i);
    cout << setprecision(20) << fixed << 1.L * dp[k][n] << '\n';
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
