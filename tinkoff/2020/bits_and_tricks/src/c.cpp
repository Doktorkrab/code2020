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
const int MAXN = 45;
const int MAXL = 20;
ll matrix[MAXN];
int dp1[1 << MAXL];
int dp2[1 << MAXL];

int solve() {
    if (!(cin >> n >> k))
        return 1;
    int x;
    for (int i = 0; i < n; i++) {
        matrix[i] = 0;
        for (int j = 0; j < n; j++) {
            cin >> x;
            if (x)
                matrix[i] |= (1LL << j);
        }
    }
    int cnt1 = n / 2;
    for (int mask = 0; mask < (1 << cnt1); mask++) {
        for (int i = 0; i < cnt1; i++) {
            if ((mask >> i) & 1)
                continue;
            if ((mask & matrix[i]) != mask)
                continue;
            dp1[mask ^ (1 << i)] = max(dp1[mask ^ (1 << i)], dp1[mask] + 1);
        }
    }
    int cnt2 = n - cnt1;
    for (int mask = 0; mask < (1 << cnt2); mask++) {
        for (int i = 0; i < cnt2; i++) {
            if ((mask >> i) & 1)
                continue;
            int good = ((mask & (matrix[i + cnt1] >> cnt1)) == mask);
            dp2[mask ^ (1 << i)] = max(dp2[mask ^ (1 << i)], dp2[mask] + good);
        }
    }
    int best_ans = 0;
    for (int mask = 0; mask < (1 << cnt1); mask++) {
        int cnt = dp1[mask];
        ll now_matrix = ((1 << cnt2) - 1);
        for (int i = 0; i < cnt1; i++) {
            if ((mask >> i) & 1) {
                now_matrix &= (matrix[i] >> cnt1);
            }
        }
//        cout << bitset<6>(mask) << ' ' << cnt << ' ' << bitset<6>(now_matrix) << ' ' << dp2[now_matrix] << '\n';
        best_ans = max(best_ans, cnt + dp2[now_matrix]);
    }
//    for (int i = 0; i < (1 << cnt1); i++)
//        cout << bitset<4>(i) << ' ' << dp1[i] << '\n';
//    cout << "---\n";
//
//    for (int i = 0; i < (1 << cnt2); i++)
//        cout << bitset<4>(i) << ' ' << dp2[i] << '\n';
//    cout << best_ans << '\n';
    cout << fixed << setprecision(20) << 1.L * k * k * (best_ans - 1) / 2 / best_ans << '\n';
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
