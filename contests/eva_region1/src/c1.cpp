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
const int MAXN = 15;
int arr[MAXN];
double dp[1 << MAXN];

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    dp[0] = -1e9;
    for (int i = 1; i < (1 << n); i++) {
        int cnt = 0;
        for (int j = 0; j < n; j++)
            if ((i >> j) & 1)
                dp[i] += arr[j], cnt++;
        dp[i] /= cnt;
    }
    for (int mask = 1; mask < (1 << n); mask++){
        for (int s = (mask - 1) & mask; s > 0; s = (s - 1) & mask){
            int s1 = (mask & ~s);
            dp[mask] = max(dp[mask], (dp[s] + dp[s1]) / 2.);
        }
    }
    int q;
    cin >> q;
    cout << setprecision(20) << fixed;
    for (int i = 0; i < q; i++){
        int l, r;
        cin >> l >> r;
        --l;
        int mask = ((1 << (r - l)) - 1) << l;
        cout << dp[mask] << '\n';
    }
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("c.in", "r", stdin);
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
