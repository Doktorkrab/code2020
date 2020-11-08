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

int n, m;
const int MAXN = 505;
const int MOD = 1e9 + 7;
int dp[2][MAXN][MAXN];
int a[MAXN], b[MAXN];
pair<int, pair<int, int>> have[MAXN * MAXN];
pair<int, pair<int, int>> have_rev[MAXN * MAXN];

int solve() {
    if (!(cin >> n))
        return 1;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cin >> m;
    for (int i = 0; i < m; i++)
        cin >> b[i];
    int pnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (a[i] == b[j]) {
                have[pnt] = {a[i], {i, j}};
                have_rev[pnt++] = {-a[i], {i, j}};
            }
        }
    sort(have, have + pnt);
    sort(have_rev, have_rev + pnt);
//    dp[0][0][0] = 1;
    int best_len = 0;
    int best_cnt = 0;
    for (int l = 1; l <= min(n, m); l++) {
        int sum = 0;
        int bonus = (l == 1 ? 1 : 0);
        if (l & 1){
            for (int i = 0; i < pnt; i++){
                auto [x, y] = have_rev[i].second;
                int lst_upd = a[x];
                int &d = dp[1][x + 1][y + 1];
                d = bonus;
                for (int j = i - 1; j >= 0; j--){
                    auto [x1, y1] = have_rev[j].second;
                    if (x1 < x && y1 < y && lst_upd != a[x1]){
//                        cout << lst_upd << ' ' << a[x1] << "!\n";
                        d = (1LL * d + dp[0][x1 + 1][y1 + 1]) % MOD;
                        lst_upd = a[x1];
                    }
                }
                if (i && have_rev[i].first == have_rev[i - 1].first){
                    auto [x1, y1] = have_rev[i - 1].second;
                    sum = (1LL * sum + MOD - dp[1][x1 + 1][y1 + 1]) % MOD;
                }
                sum = (1LL * sum + d) % MOD;
            }
        } else {
            for (int i = 0; i < pnt; i++){
                auto [x, y] = have[i].second;
                int lst_upd = a[x];
                int &d = dp[0][x + 1][y + 1];
                d = bonus;
                for (int j = i - 1; j >= 0; j--){
                    auto [x1, y1] = have[j].second;
                    if (x1 < x && y1 < y && lst_upd != a[x1]){
                        d = (1LL * d + dp[1][x1 + 1][y1 + 1]) % MOD;
                        lst_upd = a[x1];
                    }
                }
                if (i && have[i].first == have[i - 1].first){
                    auto [x1, y1] = have[i - 1].second;
                    sum = (1LL * sum + MOD - dp[0][x1 + 1][y1 + 1]) % MOD;
                }
                sum = (1LL * sum + d) % MOD;
            }
        }
        cout << l << ' ' << sum << '\n';
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= m; j++)
                cout << dp[l & 1][i][j] << " \n"[j == m];
        if (sum == 0){
            break;
        }
        best_len = l;
        best_cnt = sum;
    }
    cout << best_len << ' ' << best_cnt << '\n';
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
