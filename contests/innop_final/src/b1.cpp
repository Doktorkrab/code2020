#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using ll = long long;

#define int ll
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
const int MAXN = 2e5 + 7;
pair<int, int> pnts[MAXN];
int dp[MAXN][2];
pair<int, int> have[MAXN];
const int INF = 1e9;

int solve() {
    if (!(cin >> n))
        return 1;
    pnts[0] = {0, 0};
    for (int i = 1; i <= n; i++) {
        cin >> pnts[i].first >> pnts[i].second;
    }
    vector<pair<int, char>> ans;
    for (int i = 1; i <= n; i++) {
        int a = pnts[i - 1].second;
        int b = pnts[i].second;
        int c = pnts[i].first - pnts[i - 1].first;
        if ((b + c - a) % 2) {
            cout << "-1\n";
            return 0;
        }
        have[i] = {(b + c - a) / 2, (a + c - b) / 2};
        dp[i][0] = dp[i][1] = INF;
        if (have[i].first < 0 || have[i].second < 0 || have[i].first + have[i].second != c){
            cout << "-1\n";
            return 0;
        }
//        cout << have[i].first << ' ' << have[i].second << '\n';
    }
    dp[0][0] = 0;
    dp[0][1] = 0;
    for (int i = 1; i <= n; i++){
        if (have[i].first && have[i].second){
            if (i == 1){
                dp[i][0] = 2;
                dp[i][1] = 2;
            }
            else {
                dp[i][0] = (have[i - 1].second ? dp[i - 1][1] : dp[i - 1][0] + 1) + 1;
                dp[i][1] = (have[i - 1].first ? dp[i - 1][0] : dp[i - 1][1] + 1) + 1;
            }
        }
        else if (have[i].first) {
            dp[i][0] = min(dp[i - 1][0], dp[i - 1][1] + 1);
        }
        else if (have[i].second)
            dp[i][1] = min(dp[i - 1][1], dp[i - 1][0] + 1);
    }
//    for (int i = 0; i < 2; i++)
//        for (int j = 0; j <= n; j++)
//            cout << dp[j][i] << " \n"[j == n];
    int x = n;
    int y = 0;
    if (dp[n][0] > dp[n][1])
        y = 1;
    while (x > 0){
        if (y == 1){
            if (SZ(ans) && ans.back().second == '-')
                ans.back().first += have[x].second;
            else
                ans.emplace_back(have[x].second, '-');
            if (have[x].first)
                ans.emplace_back(have[x].first, '+');
            if (dp[x][1] == dp[x - 1][0] + 1)
                y = 0;
            else
                y = 1;
        }
        else {
            if (SZ(ans) && ans.back().second == '+')
                ans.back().first += have[x].first;
            else
                ans.emplace_back(have[x].first, '+');
            if (have[x].second)
                ans.emplace_back(have[x].second, '-');
            if (dp[x][0] == dp[x - 1][1] + 1)
                y = 1;
            else
                y = 0;
        }
        x--;
    }
    cout << SZ(ans) << '\n';
    reverse(ALL(ans));
    for (auto [a, b] : ans)
        cout << a << ' ' << b << '\n';
    return 0;
}

signed main() {
#ifdef LOCAL
    freopen("b.in", "r", stdin);
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
