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

int n, k;
const int MAXN = 1e5 + 7;
const int MAXK = 21;
const ll INF = 1e18;
ll hist[MAXN];
int arr[MAXN];
ll dp[MAXK][MAXN];
ll have = 0;
int mo_l = 0, mo_r = 0;

inline void add(int pos, int what) {
    have -= hist[pos] * (hist[pos] - 1) / 2;
    hist[pos] += what;
    have += hist[pos] * (hist[pos] - 1) / 2;
}

inline void shift(int nl, int tr) {
    while (mo_r < tr)
        add(arr[mo_r++], 1);
    while (mo_l > nl)
        add(arr[--mo_l], 1);
    while (mo_r > tr)
        add(arr[--mo_r], -1);
    while (mo_l < nl)
        add(arr[mo_l++], -1);
}

void div_and_conq(int tl, int tr, int l, int r, int level) {
    if (tl > tr)
        return;
    int tm = (tl + tr) / 2;
    int opt = l;
    for (int i = min(tm, r); i >= l; i--) {
        shift(i, tm + 1);
        ll now = dp[level - 1][i] + have;
        if (now < dp[level][tm + 1]) {
//            cout << l << ' ' << tm << ' ' << i << "\n\t" << now << ' ' << dp[level][tm + 1] << "\n\t\t" << have << '\n'
//                 << dp[level - 1][i] << "\n\n";
            dp[level][tm + 1] = now;
            opt = i;
        }
    }
    div_and_conq(tl, tm - 1, l, opt, level);
    div_and_conq(tm + 1, tr, opt, r, level);
}


int solve() {
    if (!(cin >> n >> k))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    for (int i = 0; i <= k; i++)
        for (int j = 0; j <= n; j++)
            dp[i][j] = INF;
    dp[0][0] = 0;
    for (int i = 1; i <= k; i++)
        div_and_conq(0, n - 1, 0, n - 1, i);

//    for (int i = 0; i <= k; i++)
//        for (int j = 0; j <= n; j++)
//            cout << dp[i][j] << " \n"[j == n];
    cout << dp[k][n] << '\n';
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
