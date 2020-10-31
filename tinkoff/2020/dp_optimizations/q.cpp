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

ll n;
const int LEN = 500;
ll dp[10][LEN];

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 1; i < 10; i++)
        dp[i][1] = 1;
//    if (n < 10) {
//        cout << n << '\n';
//        return 0;
//    }
    int len = 1;
    for (int l = 2; l < LEN; l++) {
        ll sum = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = i; j < 10; j++)
                dp[i][l] += dp[j][l - 1];
            sum += dp[i][l];
        }
//        cout << l << ' ' << sum << '\n';
    }
    ll sum = 0;
    --n;
    for (int l = 1; l < LEN; l++) {
        for (int i = 1; i < 10; i++)
            sum += dp[i][l];
//        cout << l << ' ' << sum << '\n';
        if (sum > n) {
            len = l;
            break;
        }
    }
    string ans;
//    int is_first = 1;
    int prev = 0;
//    cout << len << ' ' << n << '\n';
    while (len > 0) {
        for (int i = prev; i < 10; i++)
            if (n >= dp[i][len]) {
//                cout << "!" << len << ' ' << i << ' ' << dp[i][len] << '\n';
                n -= dp[i][len];
            } else {
//                cout << i << '\n';
                prev = i;
                ans += '0' + i;
                len--;
//                is_first = 0;
                break;
            }
    }
    cout << ans << '\n';
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
